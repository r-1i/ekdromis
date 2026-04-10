#include "HubState.h"

#include <memory>

#include "DungeonState.h"
#include "core/Intent.h"

HubState::HubState(GameStateManager& gsm, Hero& hero)
    : gsm_(gsm), hero_(hero), village_(Village(hero)) {}

void HubState::handleEvent(const sf::Event& event) {
  if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
    if (keyPressed->code == sf::Keyboard::Key::L) {
      gsm_.goToDungeon(0);
    }
    if (keyPressed->code == sf::Keyboard::Key::W) {
      if (village_.canMoveTo(hero_.getPosition() + sf::Vector2i{0, -1})) {
        hero_.setIntent(std::make_unique<Intent>(
            (hero_.getPosition() + sf::Vector2i{0, -1}), 1.f));
      }
    } else if (keyPressed->code == sf::Keyboard::Key::A) {
      if (village_.canMoveTo(hero_.getPosition() + sf::Vector2i{-1, 0})) {
        hero_.setIntent(std::make_unique<Intent>(
            hero_.getPosition() + sf::Vector2i{-1, 0}, 1.f));
      }
    } else if (keyPressed->code == sf::Keyboard::Key::S) {
      if (village_.canMoveTo(hero_.getPosition() + sf::Vector2i{0, 1})) {
        hero_.setIntent(std::make_unique<Intent>(
            hero_.getPosition() + sf::Vector2i{0, 1}, 1.f));
      }
    } else if (keyPressed->code == sf::Keyboard::Key::D) {
      if (village_.canMoveTo(hero_.getPosition() + sf::Vector2i{1, 0})) {
        hero_.setIntent(std::make_unique<Intent>(
            hero_.getPosition() + sf::Vector2i{1, 0}, 1.f));
      }
    }
  }
}

void HubState::update(float dt) {
  village_.update(dt);
  timeBeforeBeat_ -= dt;
  if (timeBeforeBeat_ <= 0.f) {
    if (hero_.hasIntent()) {
      hero_.setPosition(hero_.getIntent().moveDirection);
      hero_.resetIntent();
    }
    timeBeforeBeat_ = 1.f;
  }
}

void HubState::render(sf::RenderWindow& window) { village_.render(window); }
