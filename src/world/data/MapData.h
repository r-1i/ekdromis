#pragma once

#include <vector>

#include "core/Tile.h"
#include "world/data/EnemySpawnInfo.h"
#include "world/data/PortalSpawnInfo.h"

struct MapData {
  int width = 0;
  int height = 0;
  int musicBPM = 120;
  float timerSeconds = 180.f;
  sf::Vector2i heroSpawnPosition{3, 3};

  std::string name;
  std::string musicFileLocation;
  std::string textureFileName;

  std::vector<std::vector<unsigned int>> tiles;
  std::vector<EnemySpawnInfo> enemies;
  std::vector<PortalSpawnInfo> portals;

  int areaNumber = 0;
  int levelNumber = 0;
  unsigned int seed = 0;

  bool isValid() const { return width > 0 && height > 0 && !tiles.empty(); }

  void clear() {
    tiles.clear();
    enemies.clear();
    portals.clear();
    width = height = 0;
    musicBPM = 120;
    timerSeconds = 180.f;
    heroSpawnPosition = {3, 3};
    name.clear();
  }
};
