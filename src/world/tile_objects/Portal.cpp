#include "world/tile_objects/Portal.h"

#include "core/GameConstatns.h"
#include "entities/Hero.h"

Portal::Portal(const std::string& textureFileLocation) : sprite_(texture_) {
  health_ = 1;
  texture_.loadFromFile(textureFileLocation);
  sprite_.setTexture(texture_);
  sprite_.setTextureRect(sf::IntRect(
      {0, 0},
      {GameConstants::kHeroTextureSize, GameConstants::kHeroTextureSize}));
  sprite_.setScale(
      {GameConstants::kTileSize / static_cast<float>(GameConstants::kHeroTextureSize),
       GameConstants::kTileSize / static_cast<float>(GameConstants::kHeroTextureSize)});
}

void Portal::onHeroStepped(Hero& hero) {
  (void)hero;
  triggered_ = true;
  health_ = 0;
}

void Portal::render(sf::RenderWindow& window) {
  if (!isAlive()) {
    return;
  }
  sprite_.setPosition(
      {static_cast<float>(position_.x * GameConstants::kTileSize),
       static_cast<float>(position_.y * GameConstants::kTileSize)});
  window.draw(sprite_);
}

bool Portal::consumeTriggered() {
  const bool wasTriggered = triggered_;
  triggered_ = false;
  return wasTriggered;
}

