#include "entity.hpp"
#include "raylib.h"

Entity::Entity(Color color = GREEN,  Vec2 pos = Vec2(0,0)) {
    this->disp = color;
    this->pos = pos;
}
