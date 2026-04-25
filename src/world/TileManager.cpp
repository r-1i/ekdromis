#include "TileManager.h"

#include "core/GameConstatns.h"

void TileManager::initialize(MapData& mapData) {
  const int ts = 64;

  // Полы
  registerTile(0, 0, 0, ts);
  registerTile(1, 0, 0, ts);
  registerTile(2, 0, 0, ts);
  registerTile(3, 0, 0, ts);

  // Стены
  registerTile(4, 0, 1, ts);
  registerTile(5, 1, 1, ts);
  registerTile(6, 2, 1, ts);
  registerTile(7, 3, 1, ts);

  gridHeight_ = mapData.height;
  gridWidth_ = mapData.width;
  grid_.resize(mapData.height);
  for (auto& row : grid_) {
    row.resize(mapData.width);
  }

  for (int y = 0; y < mapData.height; ++y) {
    for (int x = 0; x < mapData.width; ++x) {
      grid_[y][x].setTextureIndex(mapData.tiles[y][x]);
    }
  }

  hero_.setPosition(mapData.heroSpawnPosition);
  if (isInsideGrid(mapData.heroSpawnPosition)) {
    grid_[mapData.heroSpawnPosition.y][mapData.heroSpawnPosition.x].setObject(&hero_);
  }

  tilesetTexture_.loadFromFile(mapData.textureFileName);
}

bool TileManager::isInsideGrid(const sf::Vector2i& position) const {
  return position.x >= 0 && position.x < gridWidth_ && position.y >= 0 &&
         position.y < gridHeight_;
}

void TileManager::tryAttackObjectAt(const sf::Vector2i& position, int damage) {
  if (!isInsideGrid(position)) {
    return;
  }

  Tile& targetTile = grid_[position.y][position.x];
  if (!targetTile.getObject()) {
    return;
  }

  targetTile.getObject()->takeDamage(damage);
  if (targetTile.getObject()->isAlive() == false) {
  }

  return;
}

bool TileManager::isHeroOnTile(const sf::Vector2i& position) const {
  return hero_.getPosition() == position;
}

void TileManager::tryMoveHero(const sf::Vector2i& direction) {
  tryMoveObject(hero_, direction);
}

bool TileManager::tryMoveObject(TileObject& object,
                                const sf::Vector2i& direction) {
  const sf::Vector2i source = object.getPosition();
  const sf::Vector2i target = source + direction;
  if (!canMoveTo(target)) {
    return false;
  }
  if (!isInsideGrid(source) || !isInsideGrid(target)) {
    return false;
  }

  Tile& sourceTile = grid_[source.y][source.x];
  Tile& targetTile = grid_[target.y][target.x];
  if (sourceTile.getObject() != &object) {
    return false;
  }

  if (&object == &hero_ && targetTile.getObject() &&
      targetTile.getObject()->isPassable()) {
    TileObject* passableObj = targetTile.getObject();
    passableObj->onHeroStepped(hero_);
    if (!passableObj->isAlive()) {
      targetTile.clearObject();
    }
  }

  sourceTile.clearObject();
  targetTile.setObject(&object);
  object.setPosition(target);
  return true;
}

bool TileManager::canMoveTo(const sf::Vector2i position) {
  if (position.x >= 0 && position.x < gridWidth_) {
    if (position.y >= 0 && position.y < gridHeight_) {
      const bool passable = grid_[position.y][position.x].getTextureIndex() <
                            GameConstants::kWallTilesStartIndex;
      if (!passable) {
        return false;
      }
      if (!grid_[position.y][position.x].hasObject()) {
        return true;
      }
      TileObject* obj = grid_[position.y][position.x].getObject();
      return obj && obj->isPassable();
    }
  }
  return false;
}

void TileManager::registerTile(unsigned int index, int x, int y, int tileSize) {
  textureRects_[index] =
      sf::IntRect({x * tileSize, y * tileSize}, {tileSize, tileSize});
}

void TileManager::render(sf::RenderWindow& window) {
  for (int y = 0; y < gridHeight_; ++y) {
    for (int x = 0; x < gridWidth_; ++x) {
      unsigned int tileTextureIndex = grid_[y][x].getTextureIndex();

      sf::IntRect texRect = getTextureRect(tileTextureIndex);

      sf::Sprite sprite(tilesetTexture_);
      sprite.setTextureRect(texRect);
      const float tileScaler = GameConstants::kTileSize / 24.f;
      sprite.setScale({.375f * tileScaler, .375f * tileScaler});
      sprite.setPosition({static_cast<float>(x * GameConstants::kTileSize),
                          static_cast<float>(y * GameConstants::kTileSize)});

      window.draw(sprite);
    }
  }
}

sf::IntRect TileManager::getTextureRect(unsigned int index) {
  return textureRects_[index];
}
