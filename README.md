Резников Ярослав Алексеевич
Версия SFML: 3.0.2

Доп. механика 1- ритм: ввод действий в окне бита по BPM музыки (World.cpp)

Доп. механика 2- увеличение урона за серию попаданий: множитель урона за streak успешных действий (World.cpp)

Паттерны:
- Game Loop (core/Game.cpp) — основной цикл: обработка событий → update → render.
- State + менеджер состояний (core/GameStateManager.* + states/IGameState.h) — хранит стек/очередь `IGameState`, прокидывает `handleEvent/update/render`, переключает состояния (например, `DungeonState`).
- Factory Method / Abstract Factory (world/factory/EnemyFactory.h + world/EnemyManager.cpp + world/factory/*Factory.h) — создание разных типов врагов через общий интерфейс фабрики.

```mermaid
classDiagram
  class Game {
    +run()
  }
  class GameStateManager {
    +handleEvent()
    +update()
    +render()
    +goToHub()
    +goToDungeon()
  }
  class IGameState {
    <<interface>>
    +handleEvent()
    +update()
    +render()
  }
  class DungeonState

  class EnemyManager {
    +initialize()
    +spawn()
  }
  class EnemyFactory {
    <<abstract>>
    +createEnemy()
  }
  class LionFactory
  class SpearmanFactory
  class ChestFactory

  Game --> GameStateManager
  GameStateManager o--> IGameState : states_
  DungeonState ..|> IGameState
  DungeonState --> EnemyManager
  EnemyManager o--> EnemyFactory : factory dict
  LionFactory ..|> EnemyFactory
  SpearmanFactory ..|> EnemyFactory
  ChestFactory ..|> EnemyFactory
```
