#pragma once

#include <optional>

#include "SFML/Graphics.hpp"
#include "core/TileObject.h"
class World;
class RenderWindow;

class Enemy : public TileObject {
 protected:
  sf::Texture texture_;
  sf::Sprite sprite_;
  std::vector<sf::Sprite> hearts_;
  sf::Texture heartsTex;
  World& world_;

  virtual std::optional<sf::Vector2i> getNextMoveDirection();

 public:
  Enemy(World& world, const std::string& textureFileLocation);
  virtual ~Enemy() = default;
  virtual void onTick();
  virtual void render(sf::RenderWindow& window);
  virtual void onDeath() override;
};
