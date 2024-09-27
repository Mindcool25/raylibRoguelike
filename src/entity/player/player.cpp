#include "player.hpp"
#include "raylib.h"

#include <iostream>

PlayerEntity::PlayerEntity(Color disp, Vec2 pos, int health) {
    this->disp = disp;
    this->pos = pos;
    this->health = health;
}

Vec2 PlayerEntity::move(Map* map) {
    // Starting position (no move)
    Vec2 mov = Vec2(0,0);
    // Get controls
    switch(GetKeyPressed()) {
        // NSEW movement
        case KEY_J: mov = Vec2(0, 1); break;
        case KEY_K: mov = Vec2(0, -1); break;
        case KEY_L: mov = Vec2(1, 0); break;
        case KEY_H: mov = Vec2(-1, 0); break;

        // Diagnals
        case KEY_Y: mov = Vec2(-1, -1); break;
        case KEY_B: mov = Vec2(-1, 1); break;
        case KEY_N: mov = Vec2(1, 1); break;
        case KEY_U: mov = Vec2(1, -1); break;
    }


    if (mov != Vec2(0,0)) {
        Vec2 newPos = mov + this->pos;
        if (Tile* curr = map->getTile(newPos); curr != nullptr)  {
            if (curr->isOpen()) {
                return newPos;
            } else if (curr->entity != nullptr) {
                // React to the entity
                curr->entity->damage(1);
            }
        }
    }
    return this->pos;
}

Action PlayerEntity::takeTurn(Map* map) {
    int cost = 3;
    int tick = 0;
    Vec2 target = Vec2(0,0);
    ActionType type = ActionType::none;

    // Starting position (no move)
    Vec2 mov = Vec2(0,0);
    // Get controls
    switch(GetKeyPressed()) {
        // NSEW movement
        case KEY_J: mov = Vec2(0, 1); break;
        case KEY_K: mov = Vec2(0, -1); break;
        case KEY_L: mov = Vec2(1, 0); break;
        case KEY_H: mov = Vec2(-1, 0); break;

        // Diagnals
        case KEY_Y: mov = Vec2(-1, -1); break;
        case KEY_B: mov = Vec2(-1, 1); break;
        case KEY_N: mov = Vec2(1, 1); break;
        case KEY_U: mov = Vec2(1, -1); break;
    }


    if (mov != Vec2(0,0)) {
        Vec2 newPos = mov + this->pos;
        if (Tile* curr = map->getTile(newPos); curr != nullptr)  {
            if (curr->isOpen()) {
                target = newPos;
                type = ActionType::move;
            }
        }
    }

    return Action{cost, tick, target, type, nullptr};
}
