#include "Hero.h"

#include "core/GameConstatns.h"

Hero::Hero() : sprite(tilesetTexture_), hitSound(buffer) {
  buffer.loadFromFile("hero_hit.ogg");
  hitSound.setBuffer(buffer);
  size_ = sf::Vector2f(GameConstants::kTileSize, GameConstants::kTileSize);
  tilesetTexture_.loadFromFile(GameConstants::kHeroTexturesTileset);
  sprite = sf::Sprite(tilesetTexture_,
                      sf::IntRect({0, 0}, {GameConstants::kHeroTextureSize,
                                           GameConstants::kHeroTextureSize}));
  health_ = 12;
}

void Hero::update(float dt) { animTime_ -= dt; }

void Hero::onTick(float timeBeforeTick) {
  if (hasAction()) {
    consumeAction(true);
    resetAction();
  }
}

void Hero::takeDamage(int amount) {
  health_ -= amount;
  hitSound.play();
  if (health_ <= 0) {
    onDeath();
  }
}

void Hero::consumeAction(bool canMove) { (void)canMove; }

void Hero::trySetAction(sf::Vector2i direction, float timeToNextBeat,
                        bool isMove) {
  if (timeToNextBeat <= .25f) {
    PlayerAction newAction;

    if (!isMove) {
      newAction.type = ActionType::Attack;
      newAction.direction = direction;
      playerAction_ = newAction;
    } else {
      if (timeToNextBeat <= .25f) {
        newAction.type = ActionType::Move;
        newAction.direction = direction;
        playerAction_ = newAction;
      }
    }
  }
}

void Hero::render(sf::RenderWindow& window) {
  if (animTime_ < 0.f) {
    animTime_ = .2f;
    sf::IntRect rect(
        {animFrame_ * GameConstants::kHeroTextureSize, 0},
        {GameConstants::kHeroTextureSize, GameConstants::kHeroTextureSize});

    sprite.setTextureRect(rect);
    animFrame_ += 1;
    if (animFrame_ > 5) {
      animFrame_ = 0;
    }
  }

  sprite.setPosition(
      {static_cast<float>(position_.x * GameConstants::kTileSize),
       static_cast<float>(position_.y * GameConstants::kTileSize)});
  sprite.setScale({GameConstants::kTileSize /
                       static_cast<float>(GameConstants::kHeroTextureSize),
                   GameConstants::kTileSize /
                       static_cast<float>(GameConstants::kHeroTextureSize)});
  window.draw(sprite);
}

void Hero::onDeath() { resetAction(); }

void Hero::resetForLevel() {
  health_ = 12;
  damageMultiplier_ = 1;
  successfulInputStreak_ = 0;
  animFrame_ = 0;
  animTime_ = 0.f;
  resetAction();
}

int Hero::getDamage() const { return damageMultiplier_; }
