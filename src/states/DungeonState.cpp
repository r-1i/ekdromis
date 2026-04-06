#include "DungeonState.h"

#include "HubState.h"

void DungeonState::handleEvent(const sf::Event& event) {
  if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::L) {
      gsm_.goToHub();
    }
  }
}

void DungeonState::update(float dt) {}

void DungeonState::render(sf::RenderWindow& window) {}
