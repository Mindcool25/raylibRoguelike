#include "entity/enemy/enemy.hpp"
#include "raylib.h"
#include "map/map.hpp"
#include "utils/vec2.hpp"
#include "entity/entity.hpp"
#include "entity/player/player.hpp"
#include "entity/enemy/enemy.hpp"

#include <iostream>
#include <memory>

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
    Map m(Vec2(800, 800));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j ++) {
            if (i == 0 || i == 9) {
                m.setWall(Vec2(i, j));
            }
            else {
                if (j == 0 || j == 9) {
                    m.setWall(Vec2(i, j));
                }
                else {
                    m.setFloor(Vec2(i, j));
                }
            }
        }
    }
    auto ePtr = std::make_shared<Entity>();
    auto pPtr = std::make_shared<Entity>();
    auto playerPtr = std::make_shared<PlayerEntity>(PlayerEntity(GREEN, Vec2(1,1), 20));
    auto enemyPtr = std::make_shared<EnemyEntity>(EnemyEntity(VIOLET, Vec2(9,9), 13));

    // Probably the better way to do this
    std::shared_ptr<Entity> testing = std::make_shared<EnemyEntity>(EnemyEntity(PINK, Vec2(2,2), 100));
    ePtr = std::static_pointer_cast<Entity>(enemyPtr);
    pPtr = std::static_pointer_cast<Entity>(playerPtr);
    std::cout << ePtr->health << std::endl;
    std::cout << pPtr->health << std::endl;
    std::cout << testing->health << std::endl;

    m.actors.push_back(ePtr);
    m.actors.push_back(pPtr);
    m.actors.push_back(testing);

    m.setEntity(ePtr);
    m.setEntity(pPtr);

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
