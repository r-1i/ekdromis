#pragma once
#include "core/GameStateManager.h"
#include "states/IGameState.h"
#include "world/Village.h"

class HubState : public IGameState {
  GameStateManager& gsm_;
  Hero& hero_;
  Village village_;

 public:
  HubState(GameStateManager& gameStateManager, Hero& hero);
  void handleEvent(const sf::Event& event) override;
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;
  bool blocksRenderBelow() { return false; }
  bool blocksUpdateBelow() { return false; }
  ~HubState() = default;
};
