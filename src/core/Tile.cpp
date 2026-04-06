#include "core/Tile.h"

bool Tile::isOccupied() const { return object_.get() != nullptr; }
TileObject& Tile::getObject() { return *object_; }
