#include "Hero.h"

Hero::Hero() {
  {
    position_ = sf::Vector2f(140.f, 140.f);
    size_ = sf::Vector2f(50.f, 50.f);
  }
}

void Hero::render(sf::RenderWindow& window) {
  sf::RectangleShape rect({size_.x, size_.y});
  rect.setOrigin({rect.getLocalBounds().position.x + (size_.x / 2.f),
                  rect.getLocalBounds().position.y + (size_.y / 2.f)});
  rect.setPosition(position_);
  rect.setFillColor(sf::Color::Blue);
  window.draw(rect);
}
