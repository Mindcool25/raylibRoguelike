#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"
#include "../utils/vec2.hpp"

class Entity {
    public:
        Entity(Color color, Vec2 pos);

        Color disp;
        Vec2 pos;

        void move();
};


#endif // ENTITY_HPP
