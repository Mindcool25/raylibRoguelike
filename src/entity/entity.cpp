#include "entity.hpp"
#include "raylib.h"
#include <iostream>

Entity::Entity(Color color,  Vec2 pos, int health) {
    this->disp = color;
    this->pos = pos;
    this->health = health;
}

Vec2 Entity::move(Map* map) {
    return Vec2(0,0);
};

void Entity::damage(int value){
    this->health -= value;
    std::cout << this->health << std::endl;
    if (this->health <=0) {
        std::cout << "DEAD" << std::endl;
    }
}

int Entity::attack() {
    int value = this->health / 5;
    return value;
}
