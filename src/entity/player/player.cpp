#include "player.hpp"
#include "raylib.h"

#include <iostream>

PlayerEntity::PlayerEntity(Color disp, Vec2 pos, int health) {
    this->disp = disp;
    this->pos = pos;
    this->health = health;
}

void PlayerEntity::move(Map* map) {
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
        Vec2 newPos = this->pos + mov;
        if (map->tryMove(newPos)) {
            map->clearEntity(this->pos);
            this->pos = newPos;
            map->setEntity(this);
        }
        else {
            Tile* tile = map->getTile(newPos);
            if (tile->entity != nullptr) {
                tile->entity->damage(1);
                std::cout << "bumping H: " << tile->entity->health << std::endl;
            }
        }
    }
}
