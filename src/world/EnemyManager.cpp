#include "EnemyManager.h"

void EnemyManager::reset() { enemies_.clear(); }

void EnemyManager::onTick() {
  const std::size_t initialSize = enemies_.size();
  for (std::size_t i = 0; i < initialSize; ++i) {
    if (enemies_[i]) {
      enemies_[i]->onTick();
    }
  }
}

void EnemyManager::cleanupDeadEnemies(TileManager& tileManager) {
  enemies_.erase(
      std::remove_if(enemies_.begin(), enemies_.end(),
                     [this, &tileManager](const std::unique_ptr<Enemy>& enemy) {
                       if (!enemy || enemy->isAlive()) return false;

                       const sf::Vector2i pos = enemy->getPosition();
                       if (tileManager.isInsideGrid(pos) &&
                           tileManager.grid_[pos.y][pos.x].getObject() ==
                               enemy.get()) {
                         tileManager.grid_[pos.y][pos.x].clearObject();
                       }
                       return true;
                     }),
      enemies_.end());
}

void EnemyManager::render(sf::RenderWindow& window) const {
  for (const auto& enemy : enemies_) {
    enemy->render(window);
  }
}

void EnemyManager::initialize(const std::vector<EnemySpawnInfo>& enemies,
                              TileManager& tileManager) {
  if (enemyFactoryDict.find("lion") == enemyFactoryDict.end()) {
    enemyFactoryDict.emplace("lion", std::make_unique<LionFactory>());
  }
  if (enemyFactoryDict.find("spearman") == enemyFactoryDict.end()) {
    enemyFactoryDict.emplace("spearman", std::make_unique<SpearmanFactory>());
  }
  if (enemyFactoryDict.find("chest") == enemyFactoryDict.end()) {
    enemyFactoryDict.emplace("chest", std::make_unique<ChestFactory>());
  }

  for (const auto& enemySpawnInfo : enemies) {
    spawn(enemySpawnInfo.name, enemySpawnInfo.position, tileManager);
  }
}

void EnemyManager::spawn(EnemyFactory* enemyFactory,
                         const sf::Vector2i& position,
                         TileManager& tileManager) {
  auto enemy = enemyFactory->createEnemy(world_);
  enemy->setPosition(position);
  addEnemy(std::move(enemy), tileManager);
}

void EnemyManager::addEnemy(std::unique_ptr<Enemy> enemy,
                            TileManager& tileManager) {
  if (!enemy) {
    return;
  }
  const sf::Vector2i position = enemy->getPosition();
  if (tileManager.isInsideGrid(position) &&
      !tileManager.grid_[position.y][position.x].hasObject()) {
    tileManager.grid_[position.y][position.x].setObject(enemy.get());
    enemies_.push_back(std::move(enemy));
  }
}

void EnemyManager::spawn(std::string name, const sf::Vector2i& position,
                         TileManager& tileManager) {
  spawn(enemyFactoryDict[name].get(), position, tileManager);
}

void EnemyManager::update(float dt) {
  for (const auto& enemy : enemies_) {
    enemy->update(dt);
  }
}
