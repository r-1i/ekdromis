#pragma once

#include "core/TileObject.h"

class Chest : public TileObject {
  // std::vector<Item> lootTable_;
  bool isOpened_;

 public:
  void interact(Hero& hero);
};
