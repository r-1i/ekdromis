#pragma once

#include "SFML/Graphics.hpp"
#include "entities/Hero.h"
class Hud {
 private:
  const Hero& hero_;

  sf::Font debugFont;
  sf::Text debugText;
  sf::Texture goodSmileTex_;
  sf::Texture defaultSmileTex_;
  sf::Texture heartsTexturesTex_;
  sf::Texture lineTex_;
  sf::Sprite smile;
  std::vector<sf::Sprite> hearts_;
  std::vector<std::unique_ptr<sf::Sprite>> smiles_;
  float timeToBeat_ = 0.f;
  float beatInterval_ = 0.f;

 public:
  Hud(const Hero& hero);
  void update(float dt, float timeToBeat, float beatInterval);
  void render(sf::RenderWindow& window);
};
