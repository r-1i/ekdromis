#include "core/Tile.h"

Tile::Tile(unsigned int textureIndex) : tileTextureIndex_(textureIndex) {
  type_ = textureIndex < 16 ? TileType::Floor : TileType::Wall;
}

Tile::Tile(TileType type) { type_ = type; }
void Tile::setTextureIndex(unsigned int index) { tileTextureIndex_ = index; }

bool Tile::isOccupied() const { return object_ != nullptr; }
bool Tile::hasObject() const { return object_ != nullptr; }
TileObject* Tile::getObject() const { return object_; }
void Tile::setObject(TileObject* object) { object_ = object; }
void Tile::clearObject() { object_ = nullptr; }
