#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "core/Intent.h"
#include "core/PlayerAction.h"
#include "core/TileObject.h"

class Hero : public TileObject {
  sf::Vector2f size_;
  sf::Texture tilesetTexture_;
  float animTime_ = 0.f;
  int animFrame_ = 0;
  std::optional<PlayerAction> playerAction_;
  sf::Sprite sprite;

 public:
  Hero();
  void render(sf::RenderWindow& window);
  void update(float dt) override;
  void onTick(float timeBeforeTick);
  void onDeath() override;
  int getDamage() const override;
  int getHealth() const override { return health_; };
  const sf::Vector2i& getPosition() const { return TileObject::getPosition(); }

  const std::optional<PlayerAction>& getAction() const { return playerAction_; }
  bool hasAction() const { return playerAction_.has_value(); }
  void consumeAction(bool canMove);
  void resetAction() { playerAction_.reset(); }
  void trySetAction(sf::Vector2i direction, float timeToNextBeat, bool isMove);
};
