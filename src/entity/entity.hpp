#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"
#include "../utils/vec2.hpp"
#include "../utils/action.hpp"

class Map;

class Entity {
    public:
        virtual ~Entity() = default;
        Entity(Color color = BLACK, Vec2 pos = Vec2(0,0), int health = 3);
        bool alive = true;

        Color disp;
        Vec2 pos;
        int health;

        virtual void damage(int value);
        virtual Action takeTurn(Map* map);
        int attack();
};

#endif // ENTITY_HPP
