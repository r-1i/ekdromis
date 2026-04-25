#include "world/tile_objects/enemies/Lion.h"

Lion::Lion(World& world, const std::string& textureFileLocation)
    : Enemy(world, textureFileLocation) {
  animationFramesCount_ = 5;
}

std::optional<sf::Vector2i> Lion::getNextMoveDirection() {
  switch (phase_) {
    case MummyPhase::MoveUp:
      phase_ = MummyPhase::WaitFirstTick;
      return sf::Vector2i{0, -1};
    case MummyPhase::WaitFirstTick:
      phase_ = MummyPhase::WaitSecondTick;
      return std::nullopt;
    case MummyPhase::WaitSecondTick:
      phase_ = MummyPhase::MoveDown;
      return std::nullopt;
    case MummyPhase::MoveDown:
      phase_ = MummyPhase::WaitForThirdTick;
      return sf::Vector2i{0, 1};
    case MummyPhase::WaitForThirdTick:
      phase_ = MummyPhase::WaitForFourthTick;
      return std::nullopt;
    case MummyPhase::WaitForFourthTick:
      phase_ = MummyPhase::MoveUp;
      return std::nullopt;
  }

  return std::nullopt;
}
