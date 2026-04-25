#pragma once

#include "SFML/Graphics.hpp"
#include "core/TileObject.h"

class Portal : public TileObject {
 public:
  explicit Portal(const std::string& textureFileLocation);
  ~Portal() override = default;

  bool isPassable() const override { return true; }
  void onHeroStepped(Hero& hero) override;
  void render(sf::RenderWindow& window);
  bool consumeTriggered();

 private:
  sf::Texture texture_;
  sf::Sprite sprite_;
  bool triggered_ = false;
};

