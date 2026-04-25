#pragma once

#include <memory>

#include "world/tile_objects/enemies/Enemy.h"

class EnemyFactory {
 public:
  EnemyFactory() = default;
  virtual std::unique_ptr<Enemy> createEnemy(World& world) = 0;
  virtual ~EnemyFactory() = default;
};
