
#include "world/tile_objects/enemies/Spearman.h"

Spearman::Spearman(World& world, const std::string& textureFileLocation)
    : Enemy(world, textureFileLocation) {}

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
