#pragma once

#include <SFML/Graphics.hpp>

#include "world/data/MapData.h"

class Level {
 protected:
  sf::Texture tilesetTexture_;
  std::string texturesFileLocation_;
  std::unordered_map<TileType, sf::IntRect> textureRects_;

  void loadTileset();
  void registerTile(TileType type, int x, int y, int tileSize = 32);
  sf::IntRect getTextureRect(TileType type);

 public:
  virtual ~Level() = default;
  virtual void initialize(const MapData& data) = 0;
  virtual void update(float dt) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
  virtual void handleTileClick(sf::Vector2i tilePos) = 0;
};
