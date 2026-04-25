cmake_minimum_required(VERSION 3.28)
project(ekdromis LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_Declare(nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(SFML nlohmann_json)

add_executable(ekdromis
    src/main.cpp
    src/core/Game.cpp
    src/core/GameStateManager.cpp
    "src/states/DungeonState.cpp"
    
    
    "src/world/World.cpp"
    src/core/Tile.cpp
    src/core/TileObject.cpp
    src/world/tile_objects/chest.cpp
    src/entities/Hero.cpp
    src/entities/Hero.h
    src/systems/save/SaveData.h 
    src/systems/save/SaveManager.h
    src/systems/save/SaveManager.cpp 
    src/core/Tile.h 
    src/core/Tile.cpp
    src/core/TileObject.h 
    src/core/TileObject.cpp
    src/world/tile_objects/Chest.h 
    "src/world/tile_objects/enemies/Enemy.h"
    "src/world/tile_objects/enemies/Enemy.cpp"
    "src/world/tile_objects/enemies/ChestEnemy.h"
    "src/world/tile_objects/enemies/ChestEnemy.cpp"
    src/world/Level.h
    src/utils/JsonLevelLoader.h
    src/utils/JsonLevelLoader.cpp  
    "src/core/GameConstatns.h" "src/core/Intent.h" "src/core/PlayerAction.h" 
    "src/core/Hud.h" "src/core/Hud.cpp"   "src/world/tile_objects/enemies/Lion.h" "src/world/tile_objects/enemies/Lion.cpp" "src/world/tile_objects/enemies/Spearman.h" "src/world/tile_objects/enemies/Spearman.cpp" "src/world/tile_objects/enemies/Spear.h" "src/world/tile_objects/enemies/Spear.cpp" "src/world/tile_objects/HeartDrop.h" "src/world/tile_objects/HeartDrop.cpp" "src/world/tile_objects/Portal.h" "src/world/tile_objects/Portal.cpp" "src/world/TileManager.h" "src/world/TileManager.cpp" "src/world/EnemyManager.h" "src/world/EnemyManager.cpp" "src/world/factory/EnemyFactory.h" "src/world/factory/LionFactory.h" "src/world/factory/SpearmanFactory.h" "src/world/factory/ChestFactory.h" "src/world/factory/PortalFactory.h" "src/world/data/EnemySpawnInfo.h" "src/world/data/PortalSpawnInfo.h" "src/world/EffectsManager.h" "src/world/EffectsManager.cpp" "src/world/Effect.h" "src/world/Effect.cpp")

target_include_directories(ekdromis PRIVATE src/) 
configure_file(${CMAKE_SOURCE_DIR}/src/Roboto-Regular.ttf 
               ${CMAKE_BINARY_DIR}/bin/Roboto-Regular.ttf COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/village_tileset.png
               ${CMAKE_BINARY_DIR}/bin/village_tileset.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/maps/map_1.json
               ${CMAKE_BINARY_DIR}/bin/map_1.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/maps/map_2.json
               ${CMAKE_BINARY_DIR}/bin/map_2.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/maps/map_3.json
               ${CMAKE_BINARY_DIR}/bin/map_3.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sounds/music_1.ogg
               ${CMAKE_BINARY_DIR}/bin/music_1.ogg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/skeleton_idle.png
               ${CMAKE_BINARY_DIR}/bin/skeleton_idle.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/smiles/smile_001.png
               ${CMAKE_BINARY_DIR}/bin/smile_001.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/smiles/smile_002.png
               ${CMAKE_BINARY_DIR}/bin/smile_002.png COPYONLY) 
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/white_line_8x32.png
               ${CMAKE_BINARY_DIR}/bin/white_line_8x32.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/heart_spritesheet.png
               ${CMAKE_BINARY_DIR}/bin/heart_spritesheet.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/lion_idle.png
               ${CMAKE_BINARY_DIR}/bin/lion_idle.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/spearman_idle.png
               ${CMAKE_BINARY_DIR}/bin/spearman_idle.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/spear.png
               ${CMAKE_BINARY_DIR}/bin/spear.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/chest.png
               ${CMAKE_BINARY_DIR}/bin/chest.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/hero_idle.png
               ${CMAKE_BINARY_DIR}/bin/hero_idle.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sprites/hero_hit.png
               ${CMAKE_BINARY_DIR}/bin/hero_hit.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sounds/enemy_hit.ogg
               ${CMAKE_BINARY_DIR}/bin/enemy_hit.ogg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/assets/sounds/hero_hit.ogg
               ${CMAKE_BINARY_DIR}/bin/hero_hit.ogg COPYONLY)
target_compile_features(ekdromis PRIVATE cxx_std_17)
target_link_libraries(ekdromis PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    nlohmann_json::nlohmann_json)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ekdromis)