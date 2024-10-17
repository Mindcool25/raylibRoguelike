#include "enemy.hpp"
#include "raylib.h"

EnemyEntity::EnemyEntity(Color color, char dispChar, Vec2 pos, int health) {
    this->disp.dispChar = dispChar;
    this->disp.color = color;
    this->pos = pos;
    this->health = health;
}
