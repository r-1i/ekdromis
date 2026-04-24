#pragma once

#include "world/tile_objects/enemies/Enemy.h"

class Lion : public Enemy {
 private:
  enum class MummyPhase {
    MoveUp,
    WaitFirstTick,
    WaitSecondTick,
    MoveDown,
    WaitForThirdTick,
    WaitForFourthTick
  };

  MummyPhase phase_ = MummyPhase::MoveUp;
  virtual std::optional<sf::Vector2i> getNextMoveDirection() override;

 public:
  Lion(World& world, const std::string& textureFileLocation);
  ~Lion() override = default;
};
