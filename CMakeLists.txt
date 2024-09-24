cmake_minimum_required(VERSION 3.0)


project(raylibProject)

add_compile_options(-Wall -g)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE)
set(BUILD_GAMES
    OFF
    CACHE BOOL "" FORCE)

add_subdirectory(libs/raylib)

add_executable(
  ${PROJECT_NAME}
  src/main.cpp
  src/map/map.cpp
  src/tile/tile.cpp
  src/game/game.cpp
  src/utils/vec2.cpp
  src/entity/entity.cpp
  src/entity/enemy/enemy.cpp
  src/scheduler/scheduler.cpp
  src/entity/player/player.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
