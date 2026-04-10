#pragma once

#include "SFML/Graphics.hpp"

class Intent {
 public:
  Intent(sf::Vector2i moveDirection, float timeBeforeBeat)
      : moveDirection(moveDirection), timeBeforeBeat(timeBeforeBeat) {};
  sf::Vector2i moveDirection;
  float timeBeforeBeat;
};
