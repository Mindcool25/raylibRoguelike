#include "enemy.hpp"
#include "raylib.h"

EnemyEntity::EnemyEntity(Color disp, Vec2 pos, int health) {
    this->disp = disp;
    this->pos = pos;
    this->health = health;
}
