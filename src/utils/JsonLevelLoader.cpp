#include "utils/JsonLevelLoader.h"

#include <algorithm>
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
    data.textureFileName = j.value("texturesFileLocation", "");
    data.timerSeconds =
        std::max(1.f, j.value("timerSeconds", data.timerSeconds));
    data.musicFileLocation = j.value("musicFileLocation", "music.ogg");
    data.musicBPM = j.value("musicBPM", j.value("bpm", data.musicBPM));
    data.musicBPM = std::max(1, data.musicBPM);
    if (j.contains("heroSpawn") && j["heroSpawn"].is_object()) {
      data.heroSpawnPosition.x =
          j["heroSpawn"].value("x", data.heroSpawnPosition.x);
      data.heroSpawnPosition.y =
          j["heroSpawn"].value("y", data.heroSpawnPosition.y);
    } else {
      data.heroSpawnPosition.x =
          j.value("heroSpawnX", data.heroSpawnPosition.x);
      data.heroSpawnPosition.y =
          j.value("heroSpawnY", data.heroSpawnPosition.y);
    }

    if (j.contains("enemies") && j["enemies"].is_array()) {
      const auto& enemiesJson = j["enemies"];

      for (const auto& enemyJson : enemiesJson) {
        if (enemyJson.is_object()) {
          int x = enemyJson.value("x", 0);
          int y = enemyJson.value("y", 0);
          std::string name = enemyJson.value("name", "enemy");

          data.enemies.push_back(EnemySpawnInfo(x, y, name));
        }
      }
    }

    if (j.contains("portals") && j["portals"].is_array()) {
      for (const auto& portalJson : j["portals"]) {
        if (!portalJson.is_object()) {
          continue;
        }
        PortalSpawnInfo info;
        info.position.x = portalJson.value("x", 0);
        info.position.y = portalJson.value("y", 0);
        data.portals.push_back(info);
      }
    }

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
