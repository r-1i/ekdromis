#pragma once
#include "core/GameStateManager.h"
#include "states/IGameState.h"
#include "world/Village.h"

class HubState : public IGameState {
 private:
  GameStateManager& gsm_;
  Hero& hero_;
  Village village_;
  sf::Vector2i heroSpawnPosition_ = {12, 12};
  float timeBeforeBeat_ = .75f;

 public:
  HubState(GameStateManager& gameStateManager, Hero& hero);
  void handleEvent(const sf::Event& event) override;
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;
  bool blocksRenderBelow() { return false; }
  bool blocksUpdateBelow() { return false; }
  ~HubState() = default;
};
