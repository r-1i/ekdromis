#include "core/Hud.h"

#include "GameConstatns.h"

Hud::Hud()
    : debugFont("Roboto-Regular.ttf"),
      debugText(debugFont),
      smile(goodSmileTex) {
  debugFont.openFromFile("Roboto-Regular.ttf");
  goodSmileTex.loadFromFile("smile_001.png");
  defaultSmileTex.loadFromFile("smile_002.png");
  lineTex_.loadFromFile("white_line_8x32.png");

  debugText = sf::Text(debugFont, "dfa", 30);
  debugText.setPosition({GameConstants::kScreenWidth - 300, 30});

  smile.setTexture(goodSmileTex, true);
  smile.setOrigin({smile.getTextureRect().size.x / 2.f,
                   smile.getTextureRect().size.y / 2.f});

  smile.setPosition({GameConstants::kScreenWidth / 2.f,
                     GameConstants::kScreenHeight - 120.f});
  smile.setScale({3.0f, 3.0f});
  for (int i = 0; i < 10; ++i) {
    smiles_.push_back(std::make_unique<sf::Sprite>(lineTex_));
    (*smiles_[i])
        .setPosition(sf::Vector2f({GameConstants::kScreenWidth - 150.f * i,
                                   GameConstants::kScreenHeight - 70.f}));
    (*smiles_[i]).setScale({1.0f, 1.0f});
  }
}

void Hud::update(float dt, float timeToBeat, float beatInterval) {
  timeToBeat_ = timeToBeat;
  beatInterval_ = beatInterval;
  for (int i = 0; i < 10; ++i) {
    if ((*smiles_[i]).getPosition().x >
        GameConstants::kScreenWidth / 2.f - 4.f) {
      (*smiles_[i])
          .setPosition(sf::Vector2f({GameConstants::kScreenWidth - 150.f * 10,
                                     GameConstants::kScreenHeight - 70.f}));
    }

    sf::Vector2f newPosition =
        (*smiles_[i]).getPosition() + sf::Vector2f(187.5f * dt, 0.f);
    (*smiles_[i]).setPosition(newPosition);
  }
}

void Hud::render(sf::RenderWindow& window) {
  debugText.setString(std::to_string(timeToBeat_));
  if (timeToBeat_ < (beatInterval_ / 2.f)) {
    smile.setTexture(goodSmileTex, true);
    smile.setScale({4.f, 4.f});

  } else {
    smile.setTexture(defaultSmileTex, true);
    smile.setScale({3.f, 3.f});
  }

  for (int i = 0; i < smiles_.size(); ++i) {
    window.draw((*smiles_[i]));
  }

  window.draw(smile);
  window.draw(debugText);
}
