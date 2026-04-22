#pragma once

#include "SFML/Graphics.hpp"

class TileObject {
 protected:
  sf::Vector2i position_;
  int health_ = 1;

 public:
  virtual ~TileObject() = default;

  virtual void update(float dt) {}
  virtual void onDeath() {}

  virtual bool isPassable() const { return false; }

  virtual void takeDamage(int amount) {
    health_ -= amount;
    if (health_ <= 0) {
      onDeath();
    }
  }

  virtual int getDamage() const { return 0; }
  virtual bool isAlive() const { return health_ > 0; }

  const sf::Vector2i& getPosition() const { return position_; }
  void setPosition(const sf::Vector2i& position) { position_ = position; }
};
