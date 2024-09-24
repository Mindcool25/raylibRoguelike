#include "game.hpp"
#include "raylib.h"

Game::Game() {
    // Setting up initial variables
    map = Map(Vec2(30, 30));
    schedule = Scheduler();
    entities = {};

    // Start up raylib init stuff
    // NOTE: Maybe not have this happen in the constructor, have it run when the game
    //       actually needs to start showing things
    InitWindow(800, 800, "Roguelike Thing"); // TODO: no hardcoded value here for later
    SetTargetFPS(60);
}

void Game::runEntities() {
    std::vector<std::shared_ptr<Entity>> remove;
    for (auto i : entities) {
        if (this->schedule.getCurrent() == i) {
            if (i->health <= 0) {
                remove.push_back(i);
                i.reset();
            } else {
                Vec2 iPos = i->move(&this->map);
                // Check if the entity actually moved, if it did, move on to next tick
                if (iPos != i->pos) {
                    this->map.getTile(i->pos)->entity = nullptr;
                    i->pos = iPos;
                    this->map.getTile(iPos)->entity = i;
                    this->schedule.tick += 1;
                }
            }
        }
    }

    // Remove entity from the tile, then remove it from the actors vector
    for (auto j : remove) {
        this->map.clearEntity(j->pos);
        this->schedule.removeEntity(j);
        std::erase(this->entities, j);
    }
}

void Game::gameLoop() {
    while (!WindowShouldClose()) {
        this->render();
        this->runEntities();
    }

    CloseWindow();
}

void Game::render() {
    BeginDrawing();
    ClearBackground(BLACK);

    map.render(10); // TODO: decide if map should actually draw itself

    EndDrawing();
}
