#pragma once

#include <vector>

#include "core/Tile.h"
#include "entities/Hero.h"

class Village {
  std::vector<std::vector<Tile>> grid_;
  Hero& hero_;

 public:
  Village(Hero& hero);
  void render(sf::RenderWindow& window);
};
