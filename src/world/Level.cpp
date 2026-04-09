#include "Level.h"

#include <iostream>

void Level::loadTileset() {
  if (!tilesetTexture_.loadFromFile(texturesFileLocation_)) {
    std::cerr << "Failed to load village tileset!\n";
  }
}

void Level::registerTile(TileType type, int x, int y, int tileSize) {
  textureRects_[type] =
      sf::IntRect({x * tileSize, y * tileSize}, {tileSize, tileSize});
}

sf::IntRect Level::getTextureRect(TileType type) { return textureRects_[type]; }
