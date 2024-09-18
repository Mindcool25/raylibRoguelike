#include "raylib.h"
#include "map/map.hpp"
#include "utils/vec2.hpp"
#include "entity/entity.hpp"

#include <iostream>

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 800;

void draw() {
    ClearBackground(BLACK);
    return;
}

void update() {
    return;
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
    Entity* e = new Entity(GREEN, Vec2(3,3));

    m.setEntity(e);

    while (!WindowShouldClose()) {
        update();
        BeginDrawing();
        draw();
        m.render(5);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
