#include "world/tile_objects/enemies/Enemy.h"

#include "core/GameConstatns.h"
#include "world/World.h"

Enemy::Enemy(World& world, const std::string& fileLocation)
    : world_(world), sprite_(texture_) {
  health_ = 8;
  texture_.loadFromFile(fileLocation);
  sprite_.setTexture(texture_, true);
  for (int i = 0; i < (health_ / 4); i++) {
    heartsTex.loadFromFile("heart_spritesheet.png");
    hearts_.push_back(sf::Sprite(heartsTex, sf::IntRect({0, 0}, {32, 32})));
  }
}

void Enemy::render(sf::RenderWindow& window) {
  sprite_.setPosition(
      {static_cast<float>(position_.x * GameConstants::kTileSize),
       static_cast<float>(position_.y * GameConstants::kTileSize)});

  sf::Vector2 heartsStartSpawnPos = sprite_.getPosition();
  heartsStartSpawnPos.x += GameConstants::kTileSize / 2;
  heartsStartSpawnPos.x -= (hearts_.size() * 32) / 2;
  int offsetY = 32;
  heartsStartSpawnPos.y -= offsetY;
  for (int i = 0; i < hearts_.size(); i++) {
    hearts_[i].setPosition(
        {heartsStartSpawnPos.x + (32 * i), heartsStartSpawnPos.y});

    const int health = getHealth();
    const int heartStart = 4 * i;
    const int heartEnd = 4 * (i + 1);
    if (health <= heartStart) {
      hearts_[i].setTextureRect(sf::IntRect({4 * 32, 0}, {32, 32}));
    } else if (health >= heartEnd) {
      hearts_[i].setTextureRect(sf::IntRect({0, 0}, {32, 32}));
    } else {
      const int frame = 4 - (health - heartStart);
      hearts_[i].setTextureRect(sf::IntRect({frame * 32, 0}, {32, 32}));
    }
    window.draw(hearts_[i]);
  }
  window.draw(sprite_);
}

void Enemy::onTick() {
  const std::optional<sf::Vector2i> direction = getNextMoveDirection();
  if (!direction.has_value()) return;
  if (!world_.tryMoveObject(*this, direction.value()) &&
      world_.isHeroOnTile(position_ + direction.value())) {
    world_.tryAttackObjectAt(position_ + direction.value(), getDamage());
  }
}

std::optional<sf::Vector2i> Enemy::getNextMoveDirection() {
  return std::nullopt;
}

void Enemy::onDeath() {}
