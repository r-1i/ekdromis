#pragma once

#include <optional>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "core/TileObject.h"
class World;
class RenderWindow;

class Enemy : public TileObject {
 protected:
  sf::Texture texture_;
  sf::Sprite sprite_;
  sf::SoundBuffer hitBuffer_;
  sf::Sound hitSound_;
  std::vector<sf::Sprite> hearts_;
  sf::Texture heartsTex;
  World& world_;
  int animationFramesCount_ = 1;
  float animTime_ = 0.f;
  float animFrameTime_ = .25f;
  int currentAnimFrame_ = 0;

  virtual std::optional<sf::Vector2i> getNextMoveDirection();

 public:
  Enemy(World& world, const std::string& textureFileLocation);
  virtual ~Enemy() = default;
  virtual void onTick();
  virtual void update(float dt);
  virtual void render(sf::RenderWindow& window);
  virtual void onDeath() override;
  virtual void takeDamage(int amount) override;
};
