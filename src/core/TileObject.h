#pragma once

#include "SFML/Graphics.hpp"
#include "entities/Hero.h"

class TileObject {
 protected:
  sf::Vector2i position_;

 public:
  virtual void interact(Hero& hero) = 0;
  virtual void update(float dt) = 0;
  bool isPassable() { return true; };
  sf::Vector2i getPosition() { return position_; };
};
