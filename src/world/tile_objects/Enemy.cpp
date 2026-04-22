#include "world/tile_objects/Enemy.h"

#include "core/GameConstatns.h"

Enemy::Enemy() {
  health_ = 3;
  shape_.setSize({static_cast<float>(GameConstants::kTileSize),
                  static_cast<float>(GameConstants::kTileSize)});
  shape_.setFillColor(sf::Color(200, 180, 90));
}

void Enemy::render(sf::RenderWindow& window) {
  shape_.setPosition(
      {static_cast<float>(position_.x * GameConstants::kTileSize),
       static_cast<float>(position_.y * GameConstants::kTileSize)});
  window.draw(shape_);
}

std::optional<sf::Vector2i> Enemy::getNextMoveDirection() {
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

void Enemy::onDeath() {}

int Enemy::getDamage() const { return 1; }
