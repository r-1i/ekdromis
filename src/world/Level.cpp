#include "Level.h"

#include <iostream>

#include "core/GameConstatns.h"

void Level::loadTileset() {
  if (!tilesetTexture_.loadFromFile(texturesFileLocation_)) {
    std::cerr << "Failed to load village tileset!\n";
  }
}

void Level::registerTile(unsigned int index, int x, int y, int tileSize) {
  textureRects_[index] =
      sf::IntRect({x * tileSize, y * tileSize}, {tileSize, tileSize});
}

sf::IntRect Level::getTextureRect(unsigned int index) {
  return textureRects_[index];
}

bool Level::canMoveTo(const sf::Vector2i position) {
  if (position.x >= 0 && position.x < 16) {
    if (position.y >= 0 && position.y < 16) {
      return mapData_.tiles[position.y][position.x] <
             GameConstants::wallTilesStartIndex_;
    }
  }
  return false;
}
