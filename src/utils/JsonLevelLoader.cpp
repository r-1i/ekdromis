#include "utils/JsonLevelLoader.h"

#include <fstream>
#include <iostream>

MapData JsonLevelLoader::load(const std::string& fileName) {
  MapData data;
  data.clear();

  try {
    std::ifstream file(fileName);
    if (!file.is_open()) {
      throw std::runtime_error("Cannot open level file: " + fileName);
    }

    nlohmann::json j = nlohmann::json::parse(file);

    // Основная информация
    data.name = j.value("name", "Unnamed Level");
    data.width = j.value("width", 0);
    data.height = j.value("height", 0);
    data.areaNumber = j.value("areaNumber", 0);
    data.levelNumber = j.value("levelNumber", 0);
    data.seed = j.value("seed", 0u);
    data.textureFileLocation = j.value("texturesFileLocation", "");

    data.bpm = 100;
    data.musicFileLocation = "music.ogg";

    // Загрузка тайлов
    if (!j.contains("tiles") || !j["tiles"].is_array()) {
      throw std::runtime_error("Missing or invalid 'tiles' array in " +
                               fileName);
    }

    const auto& tilesJson = j["tiles"];

    if (tilesJson.size() != static_cast<size_t>(data.height)) {
      throw std::runtime_error("Height mismatch in JSON file: " + fileName);
    }

    data.tiles.resize(data.height);

    for (size_t y = 0; y < tilesJson.size(); ++y) {
      const auto& row = tilesJson[y];

      if (!row.is_array() || row.size() != static_cast<size_t>(data.width)) {
        throw std::runtime_error("Invalid row size at y=" + std::to_string(y));
      }

      data.tiles[y].resize(data.width);

      for (size_t x = 0; x < row.size(); ++x) {
        int tileId = row[x].get<int>();
        data.tiles[y][x] = static_cast<unsigned int>(tileId);
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Error loading level '" << fileName << "': " << e.what()
              << std::endl;
    data.clear();  // возвращаем невалидную карту
  }

  return data;
}
