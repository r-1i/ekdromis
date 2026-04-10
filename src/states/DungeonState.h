#pragma once
#include "core/GameStateManager.h"
#include "entities/Hero.h"
#include "states/IGameState.h"
#include "world/World.h"

class DungeonState : public IGameState {
  GameStateManager& gsm_;
  Hero& hero_;
  World world_;
  int area_;
  sf::Vector2i heroSpawnPosition_;

 public:
  DungeonState(GameStateManager& gsm, Hero& hero, int area)
      : gsm_(gsm), hero_(hero), area_(area) {};
  void handleEvent(const sf::Event& event) override;
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;
  bool blocksRenderBelow() { return false; }
  bool blocksUpdateBelow() { return false; }
  ~DungeonState() = default;
};
