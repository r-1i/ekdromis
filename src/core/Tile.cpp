#include "core/Tile.h"

Tile::Tile(unsigned int textureIndex) : tileTextureIndex_(textureIndex) {
  type_ = textureIndex < 16 ? TileType::Floor : TileType::Wall;
}

Tile::Tile(TileType type) { type_ = type; }
void Tile::setTextureIndex(unsigned int index) { tileTextureIndex_ = index; }

bool Tile::isOccupied() const { return object_.get() != nullptr; }
TileObject& Tile::getObject() { return *object_; }
