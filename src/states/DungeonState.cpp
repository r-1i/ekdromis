#include "DungeonState.h"

#include <memory>

#include "DungeonState.h"
#include "core/Intent.h"

DungeonState::DungeonState(GameStateManager& gsm, Hero& hero, int area)
    : gsm_(gsm), hero_(hero), village_(World(hero, area)), area_(area) {}

void DungeonState::handleEvent(const sf::Event& event) {
  if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::L) {
      gsm_.goToDungeon(1);
    } else {
      village_.handleEvent(event);
    }
  }
}

void DungeonState::update(float dt) {
  village_.update(dt);
  if (village_.consumePortalTriggered()) {
    gsm_.reloadState(area_ + 1);
    return;
  }
  if (village_.isHeroDead() || village_.isTimerEnded()) {
    gsm_.reloadState(area_);
  }
}

void DungeonState::render(sf::RenderWindow& window) { village_.render(window); }
