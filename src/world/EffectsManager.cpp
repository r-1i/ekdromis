#include "world/EffectsManager.h"

#include <algorithm>

void EffectsManager::spawn(EffectType type, const sf::Vector2f& position) {
  switch (type) {
    case EffectType::HeroAttack: {
      effects_.push_back(
          std::make_unique<Effect>("hero_hit.png", position, 16, 0.02f));
      break;
    }
    case EffectType::EnemyAttack: {
      effects_.push_back(
          std::make_unique<Effect>("hero_hit.png", position, 16, 0.02f));
      break;
    }
    default: {
      break;
    }
  }
}

void EffectsManager::update(float dt) {
  for (const auto& effect : effects_) {
    effect->update(dt);
  }
}

void EffectsManager::render(sf::RenderWindow& window) {
  for (const auto& effect : effects_) {
    effect->render(window);
  }
}

void EffectsManager::cleanupEffects() {
  effects_.erase(std::remove_if(effects_.begin(), effects_.end(),
                                [](const std::unique_ptr<Effect>& e) {
                                  return e->isAnimationEnded();
                                }),
                 effects_.end());
}

void EffectsManager::reset() { effects_.clear(); }
