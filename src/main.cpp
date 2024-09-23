#include "raylib.h"
#include "map/map.hpp"
#include "utils/vec2.hpp"
#include "entity/entity.hpp"
#include "entity/player/player.hpp"
#include "entity/enemy/enemy.hpp"

#include <iostream>
#include <memory>

// TODO: Rewrite most things to work with a main game object
// TODO: Implement items, inventories
// TODO: Change rendering to be done with ASCII rather than colored squares.

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 800;

void draw() {
    ClearBackground(BLACK);
    return;
}

void update() {
    return;
}

bool isShiftDown() {
    return IsKeyDown(KEY_LEFT_SHIFT);
}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Project");
    SetTargetFPS(60);


    // Setup here
    // TODO: move map gen into the map class
    Map m(Vec2(80, 80));

    // Probably the better way to do this
    std::shared_ptr<Entity> enemy = std::make_shared<EnemyEntity>(EnemyEntity(PINK, Vec2(2,2), 10));
    std::shared_ptr<Entity> player = std::make_shared<PlayerEntity>(PlayerEntity(GREEN, Vec2(2,3), 13));

    m.actors.push_back(enemy);
    m.actors.push_back(player);

    m.setEntity(enemy);
    m.setEntity(player);


    // Schedule 100 moves
    // TODO: figure out how to make entities schedule themselves somehow
    for (int i = 0; i < 100; i++) {
        if (i%2 == 0) {
            m.schedule.scheduleEvent(i, player);
        }
        else {
            m.schedule.scheduleEvent(i, enemy);
        }
    }

    // Get rid of the shared pointers we don't need
    enemy.reset();
    player.reset();

    // Main game loop
    while (!WindowShouldClose()) {
        update();
        m.runActors();
        BeginDrawing();
        draw();
        m.render(10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
