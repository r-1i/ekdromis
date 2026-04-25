#include "GameStateManager.h";

#include "states/DungeonState.h";

int GameStateManager::normalizeDungeonArea(int area) const {
  constexpr int kMinArea = 1;
  constexpr int kMaxArea = 3;
  if (area < kMinArea) {
    return kMinArea;
  }
  if (area > kMaxArea) {
    return kMinArea;
  }
  return area;
}

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
  clearAndPush(std::make_unique<DungeonState>(*this, game_.getHero(), 1));
}

void GameStateManager::goToDungeon(int area) {
  clearAndPush(std::make_unique<DungeonState>(
      *this, game_.getHero(), normalizeDungeonArea(area)));
}

void GameStateManager::reloadState(int area) {
  pendingReloadArea_ = normalizeDungeonArea(area);
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

  if (pendingReloadArea_.has_value()) {
    const int area = pendingReloadArea_.value();
    pendingReloadArea_.reset();
    popState();
    pushState(std::make_unique<DungeonState>(*this, game_.getHero(), area));
  }
}

void GameStateManager::render(sf::RenderWindow& window) {
  if (states_.empty()) return;

  for (const auto& state : states_) {
    state->render(window);

    if (state->blocksRenderBelow()) break;
  }
}
