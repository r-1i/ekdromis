#pragma once

#include "SFML/Graphics.hpp"

class Effect {
 public:
  Effect(const std::string& fileName, const sf::Vector2f& position,
         const int animFramesCount, const float animFrameTime);
  void update(float dt);
  void render(sf::RenderWindow& window);
  bool isAnimationEnded() const { return animFrame_ >= (animFramesCount_ - 1); }

 private:
  sf::Texture texture_;
  sf::Sprite sprite_;

  int animFrame_ = 0;
  int animFramesCount_ = 16;
  float currentFrameTime_ = 0.f;
  float frameTime_ = 0.f;
};
