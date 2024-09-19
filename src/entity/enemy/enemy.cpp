#include "enemy.hpp"
#include <iostream>

EnemyEntity::EnemyEntity(Color disp, Vec2 pos, int health) {
    this->disp = disp;
    this->pos = pos;
    this->health = health;
}

Vec2 EnemyEntity::move(Map* map) {
    if (this->health <= 0 && alive) {
        map->clearEntity(this->pos);
        alive = !alive;
    }
    return this->pos;
}
