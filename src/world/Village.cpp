#include "Village.h"

#include <iostream>

#include "SFML/Audio.hpp"
#include "utils/JsonLevelLoader.h"

Village::Village(Hero& hero) : hero_(hero), music() { initialize(); }

void Village::initialize() {
  hero_.setPosition(heroSpawnPosition_);
  music.openFromFile("music.ogg");
  std::cerr << "try loading music.ogg\n";
  music.setVolume(100.f);
  music.setLooping(true);
  music.play();
  texturesFileLocation_ = "village_tileset.png";
  loadTileset();
  const int ts = 128;

  // Полы
  registerTile(0, 0, 0, ts);
  registerTile(1, 1, 0, ts);
  registerTile(2, 2, 0, ts);
  registerTile(3, 3, 0, ts);

  // Стены
  registerTile(4, 0, 1, ts);
  registerTile(5, 1, 1, ts);
  registerTile(6, 2, 1, ts);
  registerTile(7, 3, 1, ts);

  MapData data = JsonLevelLoader::load("village.json");

  initialize(data);
}

void Village::initialize(const MapData& data) {
  if (!data.isValid()) {
    std::runtime_error("MapData for Village is not valid.");
    return;
  }

  mapData_ = data;
  gridHeight_ = data.height;
  gridWidth_ = data.width;
  grid_.resize(data.height);
  for (auto& row : grid_) {
    row.resize(data.width);
  }

  for (int y = 0; y < data.height; ++y) {
    for (int x = 0; x < data.width; ++x) {
      grid_[y][x].setTextureIndex(mapData_.tiles[y][x]);
    }
  }
}

void Village::update(float dt) { hero_.update(dt); }

void Village::render(sf::RenderWindow& window) {
  for (int y = 0; y < gridHeight_; ++y) {
    for (int x = 0; x < gridWidth_; ++x) {
      unsigned int tileTextureIndex = grid_[y][x].getTextureIndex();

      sf::IntRect texRect = getTextureRect(tileTextureIndex);

      sf::Sprite sprite(tilesetTexture_);
      sprite.setTextureRect(texRect);
      sprite.setScale({.375f, .375f});
      sprite.setPosition({static_cast<float>(x * mapData_.tileSize),
                          static_cast<float>(y * mapData_.tileSize)});

      window.draw(sprite);
    }
  }

  hero_.render(window);
}

void Village::handleTileClick(sf::Vector2i tilePos) {}
