#include "core/Hud.h"

#include <string>

#include "GameConstatns.h"

Hud::Hud(const Hero& hero)
    : hero_(hero),
      debugFont("Roboto-Regular.ttf"),
      debugText(debugFont),
      damageMultiplierText(debugFont),
      comboStreakText(debugFont),
      matchTimerText(debugFont),
      smile(goodSmileTex_) {
  debugFont.openFromFile("Roboto-Regular.ttf");
  goodSmileTex_.loadFromFile("smile_001.png");
  defaultSmileTex_.loadFromFile("smile_002.png");
  lineTex_.loadFromFile("white_line_8x32.png");
  heartsTexturesTex_.loadFromFile("heart_spritesheet.png");

  debugText = sf::Text(debugFont, "dfa", 30);
  debugText.setPosition({GameConstants::kScreenWidth - 300, 30});
  damageMultiplierText = sf::Text(debugFont, "DMG x1", 26);
  damageMultiplierText.setPosition({12.f, 8.f});
  comboStreakText = sf::Text(debugFont, "Streak: 0", 22);
  comboStreakText.setPosition({12.f, 38.f});
  matchTimerText = sf::Text(debugFont, "03:00", 32);
  matchTimerText.setPosition({GameConstants::kScreenWidth * 0.5f - 50.f, 8.f});

  sf::Sprite heartSprite(heartsTexturesTex_, sf::IntRect({0, 0}, {32, 32}));
  const int heartsScale = 2;
  hearts_.push_back(heartSprite);
  hearts_.push_back(heartSprite);
  hearts_.push_back(heartSprite);

  hearts_[0].setScale({heartsScale, heartsScale});
  hearts_[1].setScale({heartsScale, heartsScale});
  hearts_[2].setScale({heartsScale, heartsScale});

  hearts_[0].setPosition({GameConstants::kScreenWidth - (96 * heartsScale), 0});
  hearts_[1].setPosition({GameConstants::kScreenWidth - (64 * heartsScale), 0});
  hearts_[2].setPosition({GameConstants::kScreenWidth - (32 * heartsScale), 0});

  smile.setTexture(goodSmileTex_, true);
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

void Hud::update(float dt, float timeToBeat, float beatInterval,
                 float remainingMatchTimeSec) {
  (void)dt;
  timeToBeat_ = timeToBeat;
  beatInterval_ = beatInterval;
  remainingMatchTimeSec_ = remainingMatchTimeSec;
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
  const int totalSeconds = static_cast<int>(remainingMatchTimeSec_);
  const int minutes = totalSeconds / 60;
  const int seconds = totalSeconds % 60;
  std::string timerLabel = (minutes < 10 ? "0" : "") + std::to_string(minutes) +
                           ":" + (seconds < 10 ? "0" : "") +
                           std::to_string(seconds);
  debugText.setString(std::to_string(timeToBeat_));
  damageMultiplierText.setString("DMG x" +
                                 std::to_string(hero_.getDamageMultiplier()));
  comboStreakText.setString("Streak: " +
                            std::to_string(hero_.getSuccessfulInputStreak()));
  matchTimerText.setString(timerLabel);
  const auto timerBounds = matchTimerText.getLocalBounds();
  matchTimerText.setPosition(
      {GameConstants::kScreenWidth * 0.5f - timerBounds.size.x * 0.5f, 8.f});
  if (timeToBeat_ < (beatInterval_ / 2.f)) {
    smile.setTexture(goodSmileTex_, true);
    smile.setScale({4.f, 4.f});

  } else {
    smile.setTexture(defaultSmileTex_, true);
    smile.setScale({3.f, 3.f});
  }

  // for (int i = 0; i < smiles_.size(); ++i) {
  //   window.draw((*smiles_[i]));
  // }

  for (int i = 0; i < 3; i++) {
    const int health = hero_.getHealth();
    const int heartStart = 4 * i;
    const int heartEnd = 4 * (i + 1);
    if (health <= heartStart) {
      hearts_[i].setTextureRect(sf::IntRect({4 * 32, 0}, {32, 32}));
    } else if (health >= heartEnd) {
      hearts_[i].setTextureRect(sf::IntRect({0, 0}, {32, 32}));
    } else {
      const int frame = 4 - (health - heartStart);
      hearts_[i].setTextureRect(sf::IntRect({frame * 32, 0}, {32, 32}));
    }
    window.draw(hearts_[i]);
  }
  window.draw(smile);
  window.draw(debugText);
  window.draw(damageMultiplierText);
  window.draw(comboStreakText);
  window.draw(matchTimerText);
}
