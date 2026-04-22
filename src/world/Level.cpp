#include "Level.h"

#include <iostream>

#include "core/GameConstatns.h"

void Level::registerTile(unsigned int index, int x, int y, int tileSize) {
  textureRects_[index] =
      sf::IntRect({x * tileSize, y * tileSize}, {tileSize, tileSize});
}

sf::IntRect Level::getTextureRect(unsigned int index) {
  return textureRects_[index];
}

bool Level::canMoveTo(const sf::Vector2i position) {
  if (position.x >= 0 && position.x < mapData_.width) {
    if (position.y >= 0 && position.y < mapData_.height) {
      const bool passable = mapData_.tiles[position.y][position.x] <
                            GameConstants::kWallTilesStartIndex;
      if (!passable) {
        return false;
      }
      return !grid_[position.y][position.x].hasObject();
    }
  }
  return false;
}
