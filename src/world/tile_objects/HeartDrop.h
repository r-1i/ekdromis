#pragma once

#include "SFML/Graphics.hpp"
#include "core/TileObject.h"

class HeartDrop : public TileObject {
 public:
  HeartDrop();
  ~HeartDrop() override = default;

  bool isPassable() const override { return true; }
  void onHeroStepped(Hero& hero) override;
  void render(sf::RenderWindow& window);

 private:
  sf::Texture texture_;
  sf::Sprite sprite_;
};

