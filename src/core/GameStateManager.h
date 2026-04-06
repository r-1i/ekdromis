#pragma once
#include <deque>
#include <memory>

#include "SFML/Graphics.hpp"
#include "core/Game.h"
#include "states/IGameState.h"

class Game;

class GameStateManager {
 private:
  std::deque<std::unique_ptr<IGameState>> states_;
  Game& game_;

 public:
  explicit GameStateManager(Game& game) : game_(game) {};
  void pushState(std::unique_ptr<IGameState> state);
  void popState();
  void clearAndPush(std::unique_ptr<IGameState> state);
  void goToHub();
  void goToDungeon(int area);
  void pushPauseMenu();

  void handleEvent(const sf::Event& event);
  void update(float dt);
  void render(sf::RenderWindow& window);
};
