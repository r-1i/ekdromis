#include "world/tile_objects/enemies/Spear.h"

#include "core/GameConstatns.h"
#include "world/World.h"

Spear::Spear(World& world, const std::string& textureFileLocation)
    : Enemy(world, textureFileLocation) {
  health_ = 1;
  animationFramesCount_ = 0;
}

std::optional<sf::Vector2i> Spear::getNextMoveDirection() {
  return sf::Vector2i{-1, 0};
}

void Spear::onTick() {
  const sf::Vector2i dir{-1, 0};
  const sf::Vector2i target = position_ + dir;

  if (!world_.tileManager_.tryMoveObject(*this, dir) &&
      world_.tileManager_.isHeroOnTile(target)) {
    world_.tileManager_.tryAttackObjectAt(target, getDamage());
    health_ = 0;
    return;
  }

  ++ticksLived_;
  if (ticksLived_ >= 3) {
    health_ = 0;
  }
}

void Spear::update(float dt) { (void)dt; }

void Spear::render(sf::RenderWindow& window) {
  sprite_.setPosition(
      {static_cast<float>(position_.x * GameConstants::kTileSize),
       static_cast<float>(position_.y * GameConstants::kTileSize)});

  window.draw(sprite_);
}
