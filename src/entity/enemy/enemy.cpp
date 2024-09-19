#include "enemy.hpp"
#include "raylib.h"
#include <iostream>

EnemyEntity::EnemyEntity(Color disp, Vec2 pos, int health) {
    this->disp = disp;
    this->pos = pos;
    this->health = health;
}

Vec2 EnemyEntity::move(Map* map) {
    Vec2 mov = Vec2(0,0);
    switch(GetRandomValue(0, 3)) {
        // NSEW movement
        case 0: mov = Vec2(0, 1); break;
        case 1: mov = Vec2(0, -1); break;
        case 2: mov = Vec2(1, 0); break;
        case 3: mov = Vec2(-1, 0); break;
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
