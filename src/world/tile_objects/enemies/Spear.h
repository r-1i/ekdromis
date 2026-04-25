#pragma once

#include "world/tile_objects/enemies/Enemy.h"

class Spear : public Enemy {
 private:
  int ticksLived_ = 0;
  std::optional<sf::Vector2i> getNextMoveDirection() override;

 public:
  Spear(World& world, const std::string& textureFileLocation);
  ~Spear() override = default;
  void onTick() override;
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;
};
