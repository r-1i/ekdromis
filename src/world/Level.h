#pragma once

#include <SFML/Graphics.hpp>

#include "world/data/MapData.h"

class Level {
 protected:
  float beatInterval_ = .8f;
  float timeToNextBeat_ = .6f;

 public:
  virtual ~Level() = default;
  virtual void initialize(const MapData& data) = 0;
  virtual void update(float dt) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
};
