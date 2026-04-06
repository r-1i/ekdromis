#include "HubState.h"

#include <memory>

#include "DungeonState.h"

HubState::HubState(GameStateManager& gsm, Hero& hero)
    : gsm_(gsm), hero_(hero), village_(Village(hero)) {}

void HubState::handleEvent(const sf::Event& event) {
  if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::L) {
      gsm_.goToDungeon(0);
    }
  }
}

void HubState::update(float dt) {}

void HubState::render(sf::RenderWindow& window) { village_.render(window); }
