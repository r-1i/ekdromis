#pragma once

#include "SFML/Graphics.hpp"

class Hud {
 private:
  sf::Font debugFont;
  sf::Text debugText;
  sf::Texture goodSmileTex;
  sf::Texture defaultSmileTex;
  sf::Texture lineTex_;
  sf::Sprite smile;
  std::vector<std::unique_ptr<sf::Sprite>> smiles_;
  float timeToBeat_;
  float beatInterval_;

 public:
  Hud();
  void update(float dt, float timeToBeat, float beatInterval);
  void render(sf::RenderWindow& window);
};
