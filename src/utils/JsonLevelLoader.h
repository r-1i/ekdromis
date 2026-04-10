#pragma once
#include <nlohmann/json.hpp>
#include <string>

#include "world/data/MapData.h"

class JsonLevelLoader {
 public:
  static MapData load(const std::string& fileName);

 private:
  JsonLevelLoader() = delete;
  ~JsonLevelLoader() = delete;
  JsonLevelLoader(const JsonLevelLoader&) = delete;
  JsonLevelLoader& operator=(const JsonLevelLoader&) = delete;
};
