#pragma once

static class GameConstants {
 public:
  static constexpr const char* kGameTitle = "Ekdromis";
  static const unsigned int kTileSize = 48;
  static const unsigned int kHeroSize = 48;
  static const unsigned int kWallTilesStartIndex = 4;
  static const unsigned int kScreenWidth = 1024;
  static const unsigned int kScreenHeight = 768;
  static constexpr const char* kHeroTexturesTileset = "skeleton_idle.png";
};
