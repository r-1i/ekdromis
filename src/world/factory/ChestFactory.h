#pragma once

#include "EnemyFactory.h"
#include "world/tile_objects/enemies/ChestEnemy.h"

class ChestFactory : public EnemyFactory {
 public:
  std::unique_ptr<Enemy> createEnemy(World& world) override {
    auto chest = std::make_unique<ChestEnemy>(world, "chest.png");
    return chest;
  }
};

