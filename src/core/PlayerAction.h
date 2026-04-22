#pragma once

enum class ActionType { Move, Attack };

struct PlayerAction {
  ActionType type = ActionType::Move;
  sf::Vector2i direction{0, 0};
};
