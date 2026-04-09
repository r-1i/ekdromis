#pragma once

#include <vector>

#include "core/Tile.h"
#include "entities/Hero.h"
#include "world/Level.h"

class Village : public Level {
 private:
  int gridWidth_;
  int gridHeight_;
  int tileSize_;
  MapData mapData_;
  std::vector<std::vector<Tile>> grid_;
  Hero& hero_;

  void initialize(const MapData& data) override;
  void initialize();

 public:
  Village(Hero& hero);
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;
  void handleTileClick(sf::Vector2i tilePos) override;
};
