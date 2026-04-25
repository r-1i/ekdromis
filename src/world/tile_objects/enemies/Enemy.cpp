#include "world/tile_objects/enemies/Enemy.h"

#include "core/GameConstatns.h"
#include "world/World.h"

Enemy::Enemy(World& world, const std::string& fileLocation)
    : world_(world), sprite_(texture_), hitSound_(hitBuffer_) {
  health_ = 8;
  texture_.loadFromFile(fileLocation);
  hitBuffer_.loadFromFile("enemy_hit.ogg");
  hitSound_.setBuffer(hitBuffer_);
  sprite_.setTexture(texture_);
  sprite_.setTextureRect(sf::IntRect({0, 0}, {96, 96}));
  sprite_.setScale({GameConstants::kTileSize /
                        static_cast<float>(GameConstants::kHeroTextureSize),
                    GameConstants::kTileSize /
                        static_cast<float>(GameConstants::kHeroTextureSize)});
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
  int offsetY = 16;
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
  if (!world_.tileManager_.tryMoveObject(*this, direction.value()) &&
      world_.tileManager_.isHeroOnTile(position_ + direction.value())) {
    world_.tileManager_.tryAttackObjectAt(position_ + direction.value(),
                                          getDamage());
  }
}

void Enemy::update(float dt) {
  if (animationFramesCount_ <= 0) {
    return;
  }
  animTime_ -= dt;
  if (animTime_ <= 0.f) {
    ++currentAnimFrame_;
    animTime_ = animFrameTime_;
    if (currentAnimFrame_ > animationFramesCount_) {
      currentAnimFrame_ = 0;
    }
    sprite_.setTextureRect(sf::IntRect(
        {currentAnimFrame_ * GameConstants::kHeroTextureSize, 0},
        {GameConstants::kHeroTextureSize, GameConstants::kHeroTextureSize}));
  }
}

std::optional<sf::Vector2i> Enemy::getNextMoveDirection() {
  return std::nullopt;
}

void Enemy::onDeath() {}

void Enemy::takeDamage(int amount) {
  health_ -= amount;
  hitSound_.play();
  if (health_ <= 0) {
    onDeath();
  }
}
