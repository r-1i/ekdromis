#pragma once
#include <memory>

#include "core/TileObject.h"

enum TileType { Empty = 0, Wall = 1 };

class Tile {
 private:
  TileType type_;
  std::unique_ptr<TileObject> object_;

 public:
  bool isOccupied() const;
  TileObject& getObject();
};
