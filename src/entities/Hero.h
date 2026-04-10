#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "core/Intent.h"

class Hero {
  sf::Vector2i position_;
  sf::Vector2f size_;
  sf::Texture tilesetTexture_;
  float animTime_ = 0.f;
  int animFrame_ = 0;
  std::unique_ptr<Intent> intent_;
  sf::Sprite sprite;

 public:
  Hero();
  void render(sf::RenderWindow& window);
  void update(float dt);

  const sf::Vector2i& getPosition() const { return position_; }

  const Intent& getIntent() const { return *intent_; }
  bool hasIntent() const { return intent_ != nullptr; }
  void resetIntent() { intent_ = nullptr; }

  void setPosition(const sf::Vector2i& position) { position_ = position; }
  void setIntent(std::unique_ptr<Intent> intent) {
    intent_ = std::move(intent);
  }
};
