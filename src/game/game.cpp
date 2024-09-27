#include "game.hpp"
#include "raylib.h"
#include <memory>

#include <iostream>

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

// TODO: this could be rewritten, its a bit hacked together
// Potential logic:
//  Get next entity in schedule NOTE: This will be an iterator
//  Ask entity to take turn until it does
//  If action is attack, check if attacked entity is dead, if so remove it
void Game::runEntities() {
    this->schedule.runCurrent(this, &this->map);
    std::vector<std::shared_ptr<Entity>> remove;
    for (auto i : entities) {
        if (i->health <= 0) {
            remove.push_back(i);
            i.reset();
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

// NOTE: probably can be improved to not be hard coded like this, who knows
void Game::handleAction(std::shared_ptr<Action> action) {
    // None shouldn't ever get here, but if it does just exit I guess
    switch (action->type) {
        case ActionType::none: return;
        case ActionType::wait: break;
        // Move is a bit chunky, could be its own function probably
        case ActionType::move:
                    this->map.getTile(action->e->pos)->entity = nullptr;
                    action->e->pos = action->target;
                    this->map.getTile(action->target)->entity = action->e;
                    action->e->pos = action->target;
                    this->schedule.tick += 1;
            break;
        case ActionType::attack: break;
        default: return;
    }
}
