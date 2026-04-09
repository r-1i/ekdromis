#pragma once
#include <memory>

#include "core/TileObject.h"

enum TileType { Floor = 0, Wall = 1, None = 2 };

class Tile {
 private:
  TileType type_ = TileType::Floor;
  std::unique_ptr<TileObject> object_;

 public:
  Tile() = default;
  explicit Tile(TileType type);

  Tile(const Tile&) = delete;
  Tile& operator=(const Tile&) = delete;

  Tile(Tile&&) noexcept = default;
  Tile& operator=(Tile&&) noexcept = default;

  void setType(TileType type) { type_ = type; }
  bool isOccupied() const;
  TileType getType() const { return type_; }
  TileObject& getObject();
};
