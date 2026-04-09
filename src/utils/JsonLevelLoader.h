#pragma once

#include <string>

#include "world/data/MapData.h"

class JsonLevelLoader {
 public:
  static MapData load(std::string fileName);
};
