#pragma once
#include "core/GameStateManager.h"
#include "states/IGameState.h"
#include "world/World.h"

class DungeonState : public IGameState {
 private:
  GameStateManager& gsm_;
  Hero& hero_;
  World village_;
  sf::Vector2i heroSpawnPosition_ = {12, 12};
  float timeBeforeBeat_ = .75f;

 public:
  DungeonState(GameStateManager& gameStateManager, Hero& hero);
  void handleEvent(const sf::Event& event) override;
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;
  bool blocksRenderBelow() const override { return false; }
  bool blocksUpdateBelow() const override { return false; }
  ~DungeonState() = default;
};
