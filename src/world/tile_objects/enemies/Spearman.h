#pragma once

#include "world/tile_objects/enemies/Enemy.h"

class Spearman : public Enemy {
 private:
  enum class SpearmanMovement {
    MoveUpFirst,
    MoveUpSecond,
    WaitFirstTick,
    MoveDownFirst,
    MoveDownSecond,
    WaitForSecondTick,
  };

  SpearmanMovement phase_ = SpearmanMovement::MoveUpFirst;
  virtual std::optional<sf::Vector2i> getNextMoveDirection() override;

 public:
  Spearman(World& world, const std::string& textureFileLocation);
  ~Spearman() override = default;
};
