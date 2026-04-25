#pragma once

#include <memory>

#include "world/tile_objects/Portal.h"

class PortalFactory {
 public:
  std::unique_ptr<Portal> createPortal() const {
    // Пока используем существующую текстуру как placeholder.
    return std::make_unique<Portal>("chest.png");
  }
};

