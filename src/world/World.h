#pragma once

#include <memory>
#include <vector>

#include "SFML/Audio.hpp"
#include "core/Hud.h"
#include "core/Tile.h"
#include "entities/Hero.h"
#include "world/EffectsManager.h"
#include "world/EnemyManager.h"
#include "world/Level.h"
#include "world/TileManager.h"
#include "world/factory/PortalFactory.h"
#include "world/tile_objects/HeartDrop.h"
#include "world/tile_objects/Portal.h"
#include "world/tile_objects/enemies/Enemy.h"

class World : public Level {
 private:
  sf::SoundBuffer musicBuffer;
  sf::Sound music_;
  Hud hud_;
  MapData mapData_;

  Hero& hero_;
  int area_ = 1;

  bool tickPerformedThisTime_ = false;
  int successfulBeatInputStreak_ = 0;
  float timer_ = 180.f;
  std::vector<std::unique_ptr<HeartDrop>> heartDrops_;
  std::vector<std::unique_ptr<Portal>> portals_;
  PortalFactory portalFactory_;
  bool portalTriggered_ = false;

  void initialize(const MapData& data) override;
  void initialize();

  sf::Vector2f currentCameraCenter_{0.f, 0.f};
  float cameraLerpFactor_ = 0.12f;
  void applyCamera(sf::RenderWindow& window);

 public:
  TileManager tileManager_;
  EnemyManager enemyManager_;
  EffectsManager effectsManager_;
  World(Hero& hero, int area = 1);

  void handleEvent(const sf::Event& event);
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;
  void tick();
  void spawnHeartDrop(const sf::Vector2i& cell);
  bool consumePortalTriggered();
  float getTimeToNextBeat() const { return timeToNextBeat_; }
  float getTimer() const { return timer_; }
  bool isTimerEnded() const { return timer_ <= 0.f; }
  bool isHeroDead() const { return hero_.getHealth() <= 0; }
};
