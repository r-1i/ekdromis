
#include "world/Effect.h"

#include "core/GameConstatns.h"

Effect::Effect(const std::string& fileName, const sf::Vector2f& position,
               const int animFramesCount, const float animFrameTime)
    : sprite_(texture_),
      animFramesCount_(animFramesCount),
      frameTime_(animFrameTime) {
  texture_.loadFromFile(fileName);
  sprite_.setTexture(texture_);
  sprite_.setScale({GameConstants::kTileSize /
                        static_cast<float>(GameConstants::kHeroTextureSize),
                    GameConstants::kTileSize /
                        static_cast<float>(GameConstants::kHeroTextureSize)});
  sprite_.setTextureRect(sf::IntRect(
      {0, 0},
      {GameConstants::kHeroTextureSize, GameConstants::kHeroTextureSize}));
  sprite_.setPosition(position);
}

void Effect::update(float dt) {
  currentFrameTime_ -= dt;
  if (currentFrameTime_ <= 0.f) {
    currentFrameTime_ = frameTime_;
    if (animFrame_ < animFramesCount_ - 2) {
      ++animFrame_;
      sprite_.setTextureRect(sf::IntRect(
          {GameConstants::kHeroTextureSize * animFrame_, 0},
          {GameConstants::kHeroTextureSize, GameConstants::kHeroTextureSize}));
    }
  }
}

void Effect::render(sf::RenderWindow& window) { window.draw(sprite_); }
