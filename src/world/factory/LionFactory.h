#pragma once

#include "EnemyFactory.h"
#include "world/tile_objects/enemies/Lion.h"

class LionFactory : public EnemyFactory {
 public:
  std::unique_ptr<Enemy> createEnemy(World& world) override {
    auto lion = std::make_unique<Lion>(world, "lion_idle.png");
    return lion;
  }
};
