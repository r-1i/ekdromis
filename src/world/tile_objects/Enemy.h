#pragma once

#include "core/TileObject.h"
class Enemy : public TileObject {
 private:
 public:
  void interact(Hero& hero);
};
