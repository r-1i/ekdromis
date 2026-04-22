#pragma once

#include <optional>

#include "core/TileObject.h"

class Enemy : public TileObject {
 private:
  enum class MummyPhase {
    MoveUp,
    WaitFirstTick,
    WaitSecondTick,
    MoveDown,
    WaitForThirdTick,
    WaitForFourthTick
  };

  sf::RectangleShape shape_;
  MummyPhase phase_ = MummyPhase::MoveUp;

 public:
  Enemy();

  void render(sf::RenderWindow& window);
  std::optional<sf::Vector2i> getNextMoveDirection();
  void onDeath() override;
  int getDamage() const override;
};
