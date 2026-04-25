#pragma once
#include "core/TileObject.h"

enum TileType { Floor = 0, Wall = 1, None = 2 };

class Tile {
 private:
  TileType type_ = TileType::Floor;
  unsigned int tileTextureIndex_ = 0;
  TileObject* object_ = nullptr;

 public:
  Tile() = default;
  Tile(unsigned int textureIndex);
  explicit Tile(TileType type);

  Tile(const Tile&) = delete;
  Tile& operator=(const Tile&) = delete;

  Tile(Tile&&) noexcept = default;
  Tile& operator=(Tile&&) noexcept = default;

  unsigned int getTextureIndex() const { return tileTextureIndex_; }
  bool isOccupied() const;
  bool hasObject() const;
  TileType getType() const { return type_; }
  TileObject* getObject() const;

  void setObject(TileObject* object);
  void clearObject();
  void setTextureIndex(unsigned int index);
};
