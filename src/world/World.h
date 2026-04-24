#pragma once

#include <memory>
#include <vector>

#include "SFML/Audio.hpp"
#include "core/Hud.h"
#include "core/Tile.h"
#include "entities/Hero.h"
#include "world/Level.h"
#include "world/tile_objects/enemies/Enemy.h"

class World : public Level {
 private:
  int gridWidth_;
  int gridHeight_;
  int tileSize_;
  sf::Music music;
  Hud hud;
  bool tickPerformedThisTime_ = false;

  Hero& hero_;
  std::vector<std::unique_ptr<Enemy>> enemies_;

  void tryMoveHero(const sf::Vector2i& direction);
  void updateEnemies();

  void initialize(const MapData& data) override;
  void initialize();

 public:
  World(Hero& hero);
  bool isInsideGrid(const sf::Vector2i& position) const;
  bool tryMoveObject(TileObject& object, const sf::Vector2i& direction);
  void tryAttackObjectAt(const sf::Vector2i& position, int damage);
  bool isHeroOnTile(const sf::Vector2i& position) const;
  void handleEvent(const sf::Event& event);
  void cleanupDeadEnemies();
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;
  void tick();
  float getTimeToNextBeat() const { return timeToNextBeat_; }
};
