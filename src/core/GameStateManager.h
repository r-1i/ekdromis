#pragma once
#include <deque>
#include <memory>
#include <optional>

#include "SFML/Graphics.hpp"
#include "core/Game.h"
#include "states/IGameState.h"

class Game;

class GameStateManager {
 private:
  std::deque<std::unique_ptr<IGameState>> states_;
  Game& game_;
  std::optional<int> pendingReloadArea_;
  int normalizeDungeonArea(int area) const;

 public:
  explicit GameStateManager(Game& game) : game_(game) {};
  void pushState(std::unique_ptr<IGameState> state);
  void popState();
  void clearAndPush(std::unique_ptr<IGameState> state);
  void goToHub();
  void goToDungeon(int area);
  void reloadState(int area);
  void pushPauseMenu();

  void handleEvent(const sf::Event& event);
  void update(float dt);
  void render(sf::RenderWindow& window);
};
