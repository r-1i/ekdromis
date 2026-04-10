#include "Hero.h"

#include "core/GameConstatns.h"

Hero::Hero() : sprite(tilesetTexture_) {
  size_ = sf::Vector2f(GameConstants::heroSize_, GameConstants::heroSize_);
  tilesetTexture_.loadFromFile("skeleton_idle.png");
  sprite = sf::Sprite(tilesetTexture_, sf::IntRect({0, 0}, {352, 352}));
}

void Hero::update(float dt) { animTime_ -= dt; }

void Hero::render(sf::RenderWindow& window) {
  if (animTime_ < 0.f) {
    animTime_ = .2f;
    sf::IntRect rect({animFrame_ * 352, 0}, {352, 352});

    sprite.setTextureRect(rect);
    animFrame_ += 1;
    if (animFrame_ > 6) {
      animFrame_ = 0;
    }
  }

  sprite.setPosition(
      {static_cast<float>(position_.x * GameConstants::tileSize_),
       static_cast<float>(position_.y * GameConstants::tileSize_)});
  sprite.setScale({48.f / 352.f, 48.f / 352.f});
  window.draw(sprite);
}
