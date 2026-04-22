#include "GameStateManager.h";

#include "states/DungeonState.h";

void GameStateManager::pushState(std::unique_ptr<IGameState> state) {
  if (state) states_.push_back(std::move(state));
}

void GameStateManager::popState() {
  if (!states_.empty()) states_.pop_back();
}

void GameStateManager::clearAndPush(std::unique_ptr<IGameState> state) {
  states_.clear();
  if (state) states_.push_back(std::move(state));
}

void GameStateManager::goToHub() {
  clearAndPush(std::make_unique<DungeonState>(*this, game_.getHero()));
}

void GameStateManager::goToDungeon(int area) {
  // clearAndPush(std::make_unique<DungeonState>(*this, game_.getHero(), area));
}

void GameStateManager::pushPauseMenu() {
  // pushState(std::make_unique<PauseState>(*this));
}

void GameStateManager::handleEvent(const sf::Event& event) {
  if (!states_.empty()) states_.back()->handleEvent(event);
}

void GameStateManager::update(float dt) {
  if (states_.empty()) return;

  for (int i = static_cast<int>(states_.size()) - 1; i >= 0; --i) {
    auto& state = states_[i];
    state->update(dt);

    if (state->blocksUpdateBelow()) break;
  }
}

void GameStateManager::render(sf::RenderWindow& window) {
  if (states_.empty()) return;

  for (const auto& state : states_) {
    state->render(window);

    if (state->blocksRenderBelow()) break;
  }
}
