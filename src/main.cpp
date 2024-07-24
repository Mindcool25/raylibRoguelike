#include "raylib.h"

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 800;


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Project");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Hello World", 10, 10, 16, GOLD);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
