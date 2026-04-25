#pragma once

#include "entities/Hero.h"
#include "world/data/MapData.h"

class TileManager {
 public:
  TileManager(Hero& hero) : hero_(hero) {};

  std::vector<std::vector<Tile>> grid_;
  sf::Texture tilesetTexture_;
  std::unordered_map<unsigned int, sf::IntRect> textureRects_;

  Hero& hero_;

  int gridWidth_;
  int gridHeight_;
  int tileSize_;

  void initialize(MapData& mapData);
  void tryMoveHero(const sf::Vector2i& direction);
  bool isInsideGrid(const sf::Vector2i& position) const;
  bool tryMoveObject(TileObject& object, const sf::Vector2i& direction);
  void tryAttackObjectAt(const sf::Vector2i& position, int damage);
  bool isHeroOnTile(const sf::Vector2i& position) const;
  bool canMoveTo(const sf::Vector2i position);

  void registerTile(unsigned int index, int x, int y, int tileSize = 32);
  void render(sf::RenderWindow& window);
  sf::IntRect getTextureRect(unsigned int index);
};
