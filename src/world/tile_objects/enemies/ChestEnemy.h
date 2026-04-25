#pragma once

#include "world/tile_objects/enemies/Enemy.h"

class ChestEnemy : public Enemy {
 public:
  ChestEnemy(World& world, const std::string& textureFileLocation);
  ~ChestEnemy() override = default;

  void onDeath() override;
  void update(float dt) override;
};

