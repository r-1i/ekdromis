#include "world/tile_objects/enemies/ChestEnemy.h"

#include "world/World.h"

ChestEnemy::ChestEnemy(World& world, const std::string& textureFileLocation)
    : Enemy(world, textureFileLocation) {
  health_ = 1;
  animationFramesCount_ = 0;
}

void ChestEnemy::onDeath() {
  if (world_.tileManager_.isInsideGrid(position_)) {
    Tile& t = world_.tileManager_.grid_[position_.y][position_.x];
    if (t.getObject() == this) {
      t.clearObject();
    }
  }

  world_.spawnHeartDrop(position_);
}

void ChestEnemy::update(float dt) { (void)dt; }

