#include "DungeonState.h"

#include <memory>

#include "DungeonState.h"
#include "core/Intent.h"

DungeonState::DungeonState(GameStateManager& gsm, Hero& hero)
    : gsm_(gsm), hero_(hero), village_(World(hero)) {}

void DungeonState::handleEvent(const sf::Event& event) {
  if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::L) {
      gsm_.goToDungeon(0);
    } else {
      village_.handleEvent(event);
    }
  }
}

void DungeonState::update(float dt) { village_.update(dt); }

void DungeonState::render(sf::RenderWindow& window) { village_.render(window); }
