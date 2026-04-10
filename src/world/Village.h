#pragma once

#include <vector>

#include "SFML/Audio.hpp"
#include "core/Tile.h"
#include "entities/Hero.h"
#include "world/Level.h"

class Village : public Level {
 private:
  int gridWidth_;
  int gridHeight_;
  int tileSize_;
  sf::Music music;

  Hero& hero_;

  void initialize(const MapData& data) override;
  void initialize();

 public:
  Village(Hero& hero);
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;
  void handleTileClick(sf::Vector2i tilePos) override;
};
