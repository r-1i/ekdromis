#pragma once

#include <memory>
#include <vector>

#include "Effect.h"
#include "TileManager.h"

enum class EffectType { HeroAttack, EnemyAttack };

class EffectsManager {
 public:
  EffectsManager() = default;
  void spawn(EffectType type, const sf::Vector2f& position);
  void update(float dt);
  void render(sf::RenderWindow& window);
  void cleanupEffects();
  void reset();

 private:
  std::vector<std::unique_ptr<Effect>> effects_;
};
