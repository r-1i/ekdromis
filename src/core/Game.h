#pragma once

#include <memory>

#include "GameStateManager.h"
#include "SFML/Graphics.hpp"
#include "entities/Hero.h"
#include "systems/save/SaveManager.h"

class GameStateManager;

class Game {
 private:
  sf::RenderWindow window_;
  std::unique_ptr<Hero> hero_;
  std::unique_ptr<GameStateManager> gsm_;
  SaveManager saveManager_;

 public:
  Game();
  void run();
  Hero& getHero() { return *hero_; }
  GameStateManager& getGameStateManager() { return *gsm_; }
  void loadGame();
  void saveGame();
};
