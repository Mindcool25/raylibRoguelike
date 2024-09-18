#include "enemy.hpp"
#include <iostream>

EnemyEntity::EnemyEntity(Color disp, Vec2 pos, int health) {
    this->disp = disp;
    this->pos = pos;
    this->health = health;
}

void EnemyEntity::move(Map* map) {
    if (this->health <= 0) {
        std::cout << "Enemy down" << std::endl;
        map->clearEntity(this->pos);
    }
    return;
}
