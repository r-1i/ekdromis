#pragma once

#include "EnemyFactory.h"
#include "world/tile_objects/enemies/Spearman.h"

class SpearmanFactory : public EnemyFactory {
 public:
  std::unique_ptr<Enemy> createEnemy(World& world) override {
    auto spearman = std::make_unique<Spearman>(world, "spearman_idle.png");
    return spearman;
  }
};
