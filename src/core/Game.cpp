#include "Game.h"

#include <memory>

#include "states/HubState.h"

Game::Game()
    : hero_(std::make_unique<Hero>()),
      gsm_(std::make_unique<GameStateManager>(*this)) {};

void Game::run() {
  window_.create(sf::VideoMode({800, 600}), "SFML works!");
  hero_ = std::make_unique<Hero>();
  getGameStateManager().goToHub();

  sf::Clock clock;

  while (window_.isOpen()) {
    const float dt = clock.restart().asSeconds();

    while (const std::optional event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window_.close();
      else {
        getGameStateManager().handleEvent(event.value());
      }
    }

    getGameStateManager().update(dt);

    window_.clear(sf::Color::Black);
    getGameStateManager().render(window_);
    window_.display();
  }
}

void Game::loadGame() {}

void Game::saveGame() {}
