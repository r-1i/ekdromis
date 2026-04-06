#pragma once
#include <SFML/Graphics.hpp>

class IGameState {
 public:
  virtual void handleEvent(const sf::Event& event) = 0;
  virtual void update(float dt) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
  virtual bool blocksUpdateBelow() const { return true; }
  virtual bool blocksRenderBelow() const { return false; }
  virtual ~IGameState() = default;
};
