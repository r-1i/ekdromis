#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Hero {
  sf::Vector2f position_;
  sf::Vector2f size_;

 public:
  Hero();
  void render(sf::RenderWindow& window);

  const sf::Vector2f& getPosition() const { return position_; }
};
