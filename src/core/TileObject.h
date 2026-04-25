#pragma once

#include "SFML/Graphics.hpp"

class Hero;

class TileObject {
 protected:
  sf::Vector2i position_;
  int health_ = 4;
  int damage_ = 1;

 public:
  virtual ~TileObject() = default;

  virtual void update(float dt) {}
  virtual void onDeath() {}

  virtual bool isPassable() const { return false; }
  virtual void onHeroStepped(Hero& hero) { (void)hero; }

  virtual void takeDamage(int amount) {
    health_ -= amount;
    if (health_ <= 0) {
      onDeath();
    }
  }

  virtual int getDamage() const { return damage_; }
  virtual bool isAlive() const { return health_ > 0; }
  virtual int getHealth() const { return health_; }
  const sf::Vector2i& getPosition() const { return position_; }
  void setPosition(const sf::Vector2i& position) { position_ = position; }
};
