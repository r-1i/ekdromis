#pragma once

static class GameConstants {
 public:
  static constexpr const char* kGameTitle = "Ekdromis";
  static const unsigned int kTileSize = 64;
  static const unsigned int kWallTilesStartIndex = 4;
  static const unsigned int kScreenWidth = 1024;
  static const unsigned int kScreenHeight = 768;
  static constexpr const char* kHeroTexturesTileset = "hero_idle.png";
  static const int kHeroTextureSize = 96;
};
