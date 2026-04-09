#include "core/Tile.h"

Tile::Tile(TileType type) { type_ = type; }

bool Tile::isOccupied() const { return object_.get() != nullptr; }
TileObject& Tile::getObject() { return *object_; }
