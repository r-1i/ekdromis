
#include "world/tile_objects/enemies/Spearman.h"

#include <memory>

#include "world/World.h"
#include "world/tile_objects/enemies/Spear.h"

Spearman::Spearman(World& world, const std::string& textureFileLocation)
    : Enemy(world, textureFileLocation) {
  animationFramesCount_ = 5;
}

void Spearman::onTick() {
  Enemy::onTick();

  if (ticksToNextSpear_ > 0) {
    --ticksToNextSpear_;
    return;
  }

  const sf::Vector2i spearSpawnCell = position_ + sf::Vector2i{-1, 0};
  if (!world_.tileManager_.isInsideGrid(spearSpawnCell) ||
      world_.tileManager_.grid_[spearSpawnCell.y][spearSpawnCell.x]
          .hasObject()) {
    return;
  }

  auto spear = std::make_unique<Spear>(world_, "spear.png");
  spear->setPosition(spearSpawnCell);
  world_.enemyManager_.addEnemy(std::move(spear), world_.tileManager_);
  ticksToNextSpear_ = 3;
}

std::optional<sf::Vector2i> Spearman::getNextMoveDirection() {
  switch (phase_) {
    case SpearmanMovement::MoveUpFirst:
      phase_ = SpearmanMovement::MoveUpSecond;
      return sf::Vector2i{0, -1};
    case SpearmanMovement::MoveUpSecond:
      phase_ = SpearmanMovement::WaitFirstTick;
      return sf::Vector2i{0, -1};
    case SpearmanMovement::WaitFirstTick:
      phase_ = SpearmanMovement::MoveDownFirst;
      return std::nullopt;
    case SpearmanMovement::MoveDownFirst:
      phase_ = SpearmanMovement::MoveDownSecond;
      return sf::Vector2i{0, 1};
    case SpearmanMovement::MoveDownSecond:
      phase_ = SpearmanMovement::WaitForSecondTick;
      return sf::Vector2i{0, 1};
    case SpearmanMovement::WaitForSecondTick:
      phase_ = SpearmanMovement::MoveUpFirst;
      return std::nullopt;
  }

  return std::nullopt;
}
