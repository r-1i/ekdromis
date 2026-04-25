#include "World.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "core/GameConstatns.h"
#include "utils/JsonLevelLoader.h"
#include "world/factory/LionFactory.h"
#include "world/tile_objects/enemies/Lion.h"
#include "world/tile_objects/enemies/Spearman.h"

void World::spawnHeartDrop(const sf::Vector2i& cell) {
  if (!tileManager_.isInsideGrid(cell)) {
    return;
  }
  if (tileManager_.grid_[cell.y][cell.x].hasObject()) {
    return;
  }

  auto drop = std::make_unique<HeartDrop>();
  drop->setPosition(cell);
  tileManager_.grid_[cell.y][cell.x].setObject(drop.get());
  heartDrops_.push_back(std::move(drop));
}

bool World::consumePortalTriggered() {
  if (!portalTriggered_) {
    return false;
  }
  portalTriggered_ = false;
  return true;
}

World::World(Hero& hero, int area)
    : hero_(hero),
      area_(area),
      music_(musicBuffer),
      hud_(hero),
      tileManager_(TileManager(hero)),
      enemyManager_(*this) {
  initialize();
}

void World::initialize() {
  const std::string mapFileName = "map_" + std::to_string(area_) + ".json";
  MapData data = JsonLevelLoader::load(mapFileName);

  initialize(data);
}

void World::applyCamera(sf::RenderWindow& window) {
  sf::View worldView = window.getDefaultView();

  const float viewHalfWidth = worldView.getSize().x * 0.5f;
  const float viewHalfHeight = worldView.getSize().y * 0.5f;

  const float worldWidth =
      static_cast<float>(tileManager_.gridWidth_ * GameConstants::kTileSize);
  const float worldHeight =
      static_cast<float>(tileManager_.gridHeight_ * GameConstants::kTileSize);

  const float heroCenterX = (static_cast<float>(hero_.getPosition().x) + 0.5f) *
                            GameConstants::kTileSize;
  const float heroCenterY = (static_cast<float>(hero_.getPosition().y) + 0.5f) *
                            GameConstants::kTileSize;

  float targetX = heroCenterX;
  float targetY = heroCenterY;

  if (worldWidth <= worldView.getSize().x) {
    targetX = worldWidth * 0.5f;
  } else {
    targetX =
        std::clamp(heroCenterX, viewHalfWidth, worldWidth - viewHalfWidth);
  }

  if (worldHeight <= worldView.getSize().y) {
    targetY = worldHeight * 0.5f;
  } else {
    targetY =
        std::clamp(heroCenterY, viewHalfHeight, worldHeight - viewHalfHeight);
  }

  sf::Vector2f target{targetX, targetY};
  currentCameraCenter_ = currentCameraCenter_ +
                         (target - currentCameraCenter_) * cameraLerpFactor_;

  worldView.setCenter(currentCameraCenter_);
  window.setView(worldView);
}

void World::initialize(const MapData& data) {
  if (!data.isValid()) {
    throw std::runtime_error("MapData for Village is not valid.");
    return;
  }

  mapData_ = data;
  timer_ = mapData_.timerSeconds;
  tickPerformedThisTime_ = false;
  successfulBeatInputStreak_ = 0;
  hero_.resetForLevel();
  hero_.setSuccessfulInputStreak(0);
  hero_.setDamageMultiplier(1);
  effectsManager_.reset();
  enemyManager_.reset();
  heartDrops_.clear();
  portals_.clear();
  portalTriggered_ = false;

  tileManager_.initialize(mapData_);

  for (const auto& portalSpawnInfo : mapData_.portals) {
    const sf::Vector2i pos = portalSpawnInfo.position;
    if (!tileManager_.isInsideGrid(pos) ||
        tileManager_.grid_[pos.y][pos.x].hasObject()) {
      continue;
    }
    auto portal = portalFactory_.createPortal();
    portal->setPosition(pos);
    tileManager_.grid_[pos.y][pos.x].setObject(portal.get());
    portals_.push_back(std::move(portal));
  }

  currentCameraCenter_ =
      sf::Vector2f({hero_.getPosition().x * GameConstants::kTileSize +
                        GameConstants::kTileSize * 0.5f,
                    hero_.getPosition().y * GameConstants::kTileSize +
                        GameConstants::kTileSize * 0.5f});

  enemyManager_.initialize(mapData_.enemies, tileManager_);

  music_.stop();
  musicBuffer.loadFromFile(data.musicFileLocation);
  music_.setBuffer(musicBuffer);
  music_.setVolume(40.f);
  music_.setLooping(true);
  music_.setPlayingOffset(sf::seconds(0.f));
  music_.play();

  beatInterval_ = (60.f / static_cast<float>(data.musicBPM));
  timeToNextBeat_ = beatInterval_ + .2f;
}

void World::update(float dt) {
  timer_ = std::max(0.f, timer_ - dt);
  if (timeToNextBeat_ <= 0) {
    {
      if (!tickPerformedThisTime_) tick();
    }
    tickPerformedThisTime_ = false;
    timeToNextBeat_ += beatInterval_;
  } else if (timeToNextBeat_ <= (beatInterval_ / 2.f)) {
    if (hero_.hasAction() && !tickPerformedThisTime_) {
      tick();
    }
  }

  hero_.update(dt);
  enemyManager_.update(dt);
  effectsManager_.update(dt);
  effectsManager_.cleanupEffects();

  heartDrops_.erase(
      std::remove_if(heartDrops_.begin(), heartDrops_.end(),
                     [this](const std::unique_ptr<HeartDrop>& d) {
                       if (!d || d->isAlive()) return false;
                       const sf::Vector2i pos = d->getPosition();
                       if (tileManager_.isInsideGrid(pos) &&
                           tileManager_.grid_[pos.y][pos.x].getObject() ==
                               d.get()) {
                         tileManager_.grid_[pos.y][pos.x].clearObject();
                       }
                       return true;
                     }),
      heartDrops_.end());

  portals_.erase(
      std::remove_if(portals_.begin(), portals_.end(),
                     [this](const std::unique_ptr<Portal>& p) {
                       if (!p || p->isAlive()) return false;
                       if (p->consumeTriggered()) {
                         portalTriggered_ = true;
                       }
                       const sf::Vector2i pos = p->getPosition();
                       if (tileManager_.isInsideGrid(pos) &&
                           tileManager_.grid_[pos.y][pos.x].getObject() ==
                               p.get()) {
                         tileManager_.grid_[pos.y][pos.x].clearObject();
                       }
                       return true;
                     }),
      portals_.end());

  hud_.update(dt, timeToNextBeat_, beatInterval_, timer_);

  timeToNextBeat_ -= dt;
}

void World::render(sf::RenderWindow& window) {
  applyCamera(window);

  tileManager_.render(window);

  hero_.render(window);
  for (const auto& portal : portals_) {
    if (portal) portal->render(window);
  }
  for (const auto& d : heartDrops_) {
    if (d) d->render(window);
  }
  enemyManager_.render(window);
  effectsManager_.render(window);
  window.setView(window.getDefaultView());
  hud_.render(window);
}

void World::tick() {
  const bool hasInputOnTick = hero_.hasAction();
  if (hero_.hasAction()) {
    const PlayerAction action = hero_.getAction().value();
    if (action.type == ActionType::Move) {
      tileManager_.tryMoveHero(action.direction);
    } else if (action.type == ActionType::Attack) {
      tileManager_.tryAttackObjectAt(hero_.getPosition() + action.direction,
                                     hero_.getDamage());
      const sf::Vector2i hitCell = hero_.getPosition() + action.direction;
      effectsManager_.spawn(
          EffectType::HeroAttack,
          sf::Vector2f(
              {static_cast<float>(hitCell.x * GameConstants::kTileSize),
               static_cast<float>(hitCell.y * GameConstants::kTileSize)}));
    }
    hero_.resetAction();
  }

  if (hasInputOnTick) {
    ++successfulBeatInputStreak_;
  } else {
    successfulBeatInputStreak_ = 0;
  }
  hero_.setSuccessfulInputStreak(successfulBeatInputStreak_);
  hero_.setDamageMultiplier(successfulBeatInputStreak_ >= 10 ? 2 : 1);

  enemyManager_.cleanupDeadEnemies(tileManager_);
  enemyManager_.onTick();

  enemyManager_.cleanupDeadEnemies(tileManager_);
  tickPerformedThisTime_ = true;
}

void World::handleEvent(const sf::Event& event) {
  if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::W) {
      sf::Vector2i direction(0, -1);
      hero_.trySetAction(
          direction, timeToNextBeat_,
          tileManager_.canMoveTo(hero_.getPosition() + direction));
    }
    if (keyPressed->code == sf::Keyboard::Key::S) {
      sf::Vector2i direction(0, 1);
      hero_.trySetAction(
          direction, timeToNextBeat_,
          tileManager_.canMoveTo(hero_.getPosition() + direction));
    }
    if (keyPressed->code == sf::Keyboard::Key::A) {
      sf::Vector2i direction(-1, 0);
      hero_.trySetAction(
          direction, timeToNextBeat_,
          tileManager_.canMoveTo(hero_.getPosition() + direction));
    }
    if (keyPressed->code == sf::Keyboard::Key::D) {
      sf::Vector2i direction(1, 0);
      hero_.trySetAction(
          direction, timeToNextBeat_,
          tileManager_.canMoveTo(hero_.getPosition() + direction));
    }
  }
}
