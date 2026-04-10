#pragma once

#include <vector>

#include "core/Tile.h"

struct MapData {
  int width = 0;
  int height = 0;
  int tileSize = 48;

  std::string name;

  std::vector<std::vector<unsigned int>> tiles;

  int areaNumber = 0;
  int levelNumber = 0;
  unsigned int seed = 0;

  bool isValid() const { return width > 0 && height > 0 && !tiles.empty(); }

  void clear() {
    tiles.clear();
    width = height = 0;
    name.clear();
  }
};
