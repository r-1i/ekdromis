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
    src/states/HubState.cpp
    src/states/DungeonState.cpp
    src/world/World.cpp
    src/world/Village.cpp
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
    src/world/tile_objects/Chest.h "src/world/tile_objects/NPC.h" "src/world/tile_objects/NPC.cpp" "src/world/tile_objects/Enemy.h" "src/world/tile_objects/Enemy.cpp")

target_include_directories(ekdromis PRIVATE src/) 

target_compile_features(ekdromis PRIVATE cxx_std_17)
target_link_libraries(ekdromis PRIVATE SFML::Graphics SFML::Window SFML::System PRIVATE nlohmann_json::nlohmann_json)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ekdromis)