#pragma once

#include <string>

#include "SFML/Graphics.hpp"

struct EnemySpawnInfo {
  EnemySpawnInfo(int x, int y, std::string name)
      : position({x, y}), name(name) {}
  std::string name;
  sf::Vector2i position;
};
