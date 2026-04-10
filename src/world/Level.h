#pragma once

#include <SFML/Graphics.hpp>

#include "world/data/MapData.h"

class Level {
 protected:
  sf::Texture tilesetTexture_;
  std::string texturesFileLocation_;
  std::unordered_map<unsigned int, sf::IntRect> textureRects_;
  sf::Vector2i heroSpawnPosition_ = {3, 3};

  MapData mapData_;
  std::vector<std::vector<Tile>> grid_;

  void loadTileset();
  void registerTile(unsigned int index, int x, int y, int tileSize = 32);
  sf::IntRect getTextureRect(unsigned int index);

 public:
  virtual ~Level() = default;
  virtual void initialize(const MapData& data) = 0;
  virtual void update(float dt) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
  virtual void handleTileClick(sf::Vector2i tilePos) = 0;
  bool canMoveTo(const sf::Vector2i position);
};
