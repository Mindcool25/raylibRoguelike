#include "game.hpp"
#include "raylib.h"
#include <memory>

#include <iostream>

Game::Game() {
    // Setting up initial variables
    map = Map(Vec2(25, 25));
    schedule = Scheduler();
    entities = {};

    // Start up raylib init stuff
    // NOTE: Maybe not have this happen in the constructor, have it run when the game
    //       actually needs to start showing things
    InitWindow(800, 800, "Roguelike Thing"); // TODO: no hardcoded value here for later
    SetTargetFPS(120);

    // Make sure to load the font after the window is created
    font = LoadFont("assets/fonts/Px437_DTK_BIOS.ttf");
}

// TODO: this could be rewritten, its a bit hacked together
// Potential logic:
//  Get next entity in schedule NOTE: This will be an iterator
//  Ask entity to take turn until it does
//  If action is attack, check if attacked entity is dead, if so remove it
void Game::runEntities() {
    // run current entities TODO: look at this again
    this->schedule.runCurrent(this, &this->map);

    // Check for dead entities and remove them
    std::vector<std::shared_ptr<Entity>> remove;
    for (auto i : entities) {
        if (i->health <= 0) {
            remove.push_back(i);
            i.reset();
        }
    }

    // Remove entity from the tile, then remove it from the entites vector
    for (auto j : remove) {
        this->map.clearEntity(j->pos);
        this->schedule.removeEntity(j);
        std::erase(this->entities, j);
    }
}

// Main game loop
void Game::gameLoop() {
    while (!WindowShouldClose()) {
        this->render();
        this->runEntities();
    }
    CloseWindow();
}

// Render loop
void Game::render() {
    BeginDrawing();
    ClearBackground(BLACK);

    map.render(10, this->font); // TODO: decide if map should actually draw itself
                                // NOTE: it is probably fine
    DrawFPS(0, 0);

    EndDrawing();
}

// NOTE: probably can be improved to not be hard coded like this, who knows
void Game::handleAction(std::shared_ptr<Action> action) {
    // None shouldn't ever get here, but if it does just exit I guess
    switch (action->type) {
        case ActionType::none:
            std::cout<< "NONE" << std::endl;
            return;

        // If the action is wait, just do nothing.
        case ActionType::wait: break;

        // Move is a bit chunky, could be its own function probably
        case ActionType::move:
            this->map.clearEntity(action->e->pos);
            action->e->pos = action->target;
            this->map.setEntity(action->e);
            break;

        // Attack given entity
        // NOTE: might need to do validation on this
        case ActionType::attack:
            this->map.getTile(action->target)->entity->damage(action->e->attack());
            break;

        // If all elses fails, just return
        default: return;
    }
}
