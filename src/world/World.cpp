#include "World.h"

#include <algorithm>
#include <iostream>

#include "SFML/Audio.hpp"
#include "core/GameConstatns.h"
#include "utils/JsonLevelLoader.h"
#include "world/tile_objects/enemies/Lion.h"
#include "world/tile_objects/enemies/Spearman.h"

World::World(Hero& hero) : hero_(hero), music(), hud(hero) { initialize(); }

bool World::isInsideGrid(const sf::Vector2i& position) const {
  return position.x >= 0 && position.x < gridWidth_ && position.y >= 0 &&
         position.y < gridHeight_;
}

bool World::tryMoveObject(TileObject& object, const sf::Vector2i& direction) {
  const sf::Vector2i source = object.getPosition();
  const sf::Vector2i target = source + direction;
  if (!canMoveTo(target)) {
    return false;
  }
  if (!isInsideGrid(source) || !isInsideGrid(target)) {
    return false;
  }

  Tile& sourceTile = grid_[source.y][source.x];
  Tile& targetTile = grid_[target.y][target.x];
  if (sourceTile.getObject() != &object) {
    return false;
  }

  sourceTile.clearObject();
  targetTile.setObject(&object);
  object.setPosition(target);
  return true;
}

bool World::isHeroOnTile(const sf::Vector2i& position) const {
  return hero_.getPosition() == position;
}

void World::tryMoveHero(const sf::Vector2i& direction) {
  tryMoveObject(hero_, direction);
}

void World::tryAttackObjectAt(const sf::Vector2i& position, int damage) {
  if (!isInsideGrid(position)) {
    return;
  }

  Tile& targetTile = grid_[position.y][position.x];
  if (!targetTile.getObject()) {
    return;
  }

  targetTile.getObject()->takeDamage(damage);
  if (targetTile.getObject()->isAlive() == false) {
    std::cerr << "kill";
  }

  return;
}

void World::updateEnemies() {
  for (const auto& enemy : enemies_) {
    enemy->onTick();
  }
}

void World::handleEvent(const sf::Event& event) {
  if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::W) {
      sf::Vector2i direction(0, -1);
      hero_.trySetAction(direction, timeToNextBeat_,
                         canMoveTo(hero_.getPosition() + direction));
    }
    if (keyPressed->code == sf::Keyboard::Key::S) {
      sf::Vector2i direction(0, 1);
      hero_.trySetAction(direction, timeToNextBeat_,
                         canMoveTo(hero_.getPosition() + direction));
    }
    if (keyPressed->code == sf::Keyboard::Key::A) {
      sf::Vector2i direction(-1, 0);
      hero_.trySetAction(direction, timeToNextBeat_,
                         canMoveTo(hero_.getPosition() + direction));
    }
    if (keyPressed->code == sf::Keyboard::Key::D) {
      sf::Vector2i direction(1, 0);
      hero_.trySetAction(direction, timeToNextBeat_,
                         canMoveTo(hero_.getPosition() + direction));
    }
  }
}

void World::initialize() {
  const int ts = 128;

  // Полы
  registerTile(0, 0, 0, ts);
  registerTile(1, 1, 0, ts);
  registerTile(2, 2, 0, ts);
  registerTile(3, 3, 0, ts);

  // Стены
  registerTile(4, 0, 1, ts);
  registerTile(5, 1, 1, ts);
  registerTile(6, 2, 1, ts);
  registerTile(7, 3, 1, ts);

  MapData data = JsonLevelLoader::load("village.json");

  initialize(data);
}

void World::initialize(const MapData& data) {
  if (!data.isValid()) {
    throw std::runtime_error("MapData for Village is not valid.");
    return;
  }

  mapData_ = data;
  gridHeight_ = data.height;
  gridWidth_ = data.width;
  grid_.resize(data.height);
  for (auto& row : grid_) {
    row.resize(data.width);
  }

  for (int y = 0; y < data.height; ++y) {
    for (int x = 0; x < data.width; ++x) {
      grid_[y][x].setTextureIndex(mapData_.tiles[y][x]);
    }
  }

  hero_.setPosition(heroSpawnPosition_);
  if (isInsideGrid(heroSpawnPosition_)) {
    grid_[heroSpawnPosition_.y][heroSpawnPosition_.x].setObject(&hero_);
  }

  tilesetTexture_.loadFromFile(data.textureFileLocation);

  enemies_.clear();
  auto mummy = std::make_unique<Lion>(*this, "lion.png");
  auto spearman = std::make_unique<Spearman>(*this, "lion.png");
  const sf::Vector2i mummySpawnPosition{8, 8};
  const sf::Vector2i spearmanSpawnPosition{12, 12};
  mummy->setPosition(mummySpawnPosition);
  spearman->setPosition(spearmanSpawnPosition);
  if (isInsideGrid(mummySpawnPosition) &&
      !grid_[mummySpawnPosition.y][mummySpawnPosition.x].hasObject()) {
    grid_[mummySpawnPosition.y][mummySpawnPosition.x].setObject(mummy.get());
    enemies_.push_back(std::move(mummy));
  }
  grid_[spearmanSpawnPosition.y][spearmanSpawnPosition.x].setObject(
      spearman.get());
  enemies_.push_back(std::move(spearman));

  beatInterval_ = (60.f / data.bpm);
  timeToNextBeat_ = beatInterval_ + .2f;
  music.openFromFile(data.musicFileLocation);
  std::cerr << "try loading music.ogg\n";
  music.setVolume(40.f);
  music.setLooping(true);
  music.play();
  std::cerr << "music.play\n";
}

void World::update(float dt) {
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
  for (const auto& enemy : enemies_) {
    enemy->update(dt);
  }
  hud.update(dt, timeToNextBeat_, beatInterval_);
  timeToNextBeat_ -= dt;
}

void World::render(sf::RenderWindow& window) {
  sf::View worldView = window.getDefaultView();

  const float viewHalfWidth = worldView.getSize().x * 0.5f;
  const float viewHalfHeight = worldView.getSize().y * 0.5f;
  const float worldWidth =
      static_cast<float>(gridWidth_ * GameConstants::kTileSize);
  const float worldHeight =
      static_cast<float>(gridHeight_ * GameConstants::kTileSize);
  const float heroCenterX = (static_cast<float>(hero_.getPosition().x) + 0.5f) *
                            GameConstants::kTileSize;
  const float heroCenterY = (static_cast<float>(hero_.getPosition().y) + 0.5f) *
                            GameConstants::kTileSize;

  float cameraX = heroCenterX;
  float cameraY = heroCenterY;

  if (worldWidth <= worldView.getSize().x) {
    cameraX = worldWidth * 0.5f;
  } else {
    cameraX =
        std::clamp(heroCenterX, viewHalfWidth, worldWidth - viewHalfWidth);
  }

  if (worldHeight <= worldView.getSize().y) {
    cameraY = worldHeight * 0.5f;
  } else {
    cameraY =
        std::clamp(heroCenterY, viewHalfHeight, worldHeight - viewHalfHeight);
  }

  worldView.setCenter({cameraX, cameraY});
  window.setView(worldView);

  for (int y = 0; y < gridHeight_; ++y) {
    for (int x = 0; x < gridWidth_; ++x) {
      unsigned int tileTextureIndex = grid_[y][x].getTextureIndex();

      sf::IntRect texRect = getTextureRect(tileTextureIndex);

      sf::Sprite sprite(tilesetTexture_);
      sprite.setTextureRect(texRect);
      const float tileScaler = GameConstants::kTileSize / 48.f;
      sprite.setScale({.375f * tileScaler, .375f * tileScaler});
      sprite.setPosition({static_cast<float>(x * GameConstants::kTileSize),
                          static_cast<float>(y * GameConstants::kTileSize)});

      window.draw(sprite);
    }
  }

  hero_.render(window);
  for (const auto& enemy : enemies_) {
    enemy->render(window);
  }

  window.setView(window.getDefaultView());
  hud.render(window);
}

void World::cleanupDeadEnemies() {
  enemies_.erase(
      std::remove_if(enemies_.begin(), enemies_.end(),
                     [this](const std::unique_ptr<Enemy>& enemy) {
                       if (!enemy || enemy->isAlive()) return false;

                       const sf::Vector2i pos = enemy->getPosition();
                       if (isInsideGrid(pos) &&
                           grid_[pos.y][pos.x].getObject() == enemy.get()) {
                         grid_[pos.y][pos.x].clearObject();
                       }
                       return true;  // удалить из enemies_
                     }),
      enemies_.end());
}

void World::tick() {
  if (hero_.hasAction()) {
    const PlayerAction action = hero_.getAction().value();
    if (action.type == ActionType::Move) {
      tryMoveHero(action.direction);
    } else if (action.type == ActionType::Attack) {
      tryAttackObjectAt(hero_.getPosition() + action.direction,
                        hero_.getDamage());
    }
    hero_.resetAction();
  }
  cleanupDeadEnemies();
  updateEnemies();
  tickPerformedThisTime_ = true;
}
