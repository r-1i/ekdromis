#include "world/tile_objects/HeartDrop.h"

#include "core/GameConstatns.h"
#include "entities/Hero.h"

HeartDrop::HeartDrop() : sprite_(texture_) {
  health_ = 1;
  texture_.loadFromFile("heart_spritesheet.png");
  sprite_.setTexture(texture_);
  sprite_.setTextureRect(sf::IntRect({0, 0}, {32, 32}));
  const float scale = GameConstants::kTileSize / 32.f;
  sprite_.setScale({scale, scale});
}

void HeartDrop::onHeroStepped(Hero& hero) {
  hero.heal(4);
  health_ = 0;
}

void HeartDrop::render(sf::RenderWindow& window) {
  sprite_.setPosition(
      {static_cast<float>(position_.x * GameConstants::kTileSize),
       static_cast<float>(position_.y * GameConstants::kTileSize)});
  window.draw(sprite_);
}

