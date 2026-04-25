#pragma once

#include <map>
#include <memory>

#include "SFML/Graphics.hpp"
#include "TileManager.h"
#include "world/factory/EnemyFactory.h"
#include "world/factory/ChestFactory.h"
#include "world/factory/LionFactory.h"
#include "world/factory/SpearmanFactory.h"
#include "world/tile_objects/enemies/Enemy.h"

class EnemyManager {
 public:
  EnemyManager(World& world) : world_(world) {};
  void initialize(const std::vector<EnemySpawnInfo>& enemies,
                  TileManager& tileManager);
  void spawn(EnemyFactory* enemyFactory, const sf::Vector2i& position,
             TileManager& tileManager);
  void spawn(std::string name, const sf::Vector2i& position,
             TileManager& tileManager);
  void addEnemy(std::unique_ptr<Enemy> enemy, TileManager& tileManager);
  void update(float dt);
  void onTick();
  void cleanupDeadEnemies(TileManager& tileManager);
  void render(sf::RenderWindow& window) const;
  void reset();

 private:
  World& world_;
  std::vector<std::unique_ptr<Enemy>> enemies_;
  std::map<std::string, std::unique_ptr<EnemyFactory>> enemyFactoryDict;
};
