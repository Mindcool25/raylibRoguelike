#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"
#include "../utils/vec2.hpp"
#include "../utils/action.hpp"
#include "../inventory/inventory.hpp"
#include <memory>
#include <string>

class Map;

/**
 * Entity
 * Base entity class
 *
 * This holds all data relating to an entity as well as
 * turn handling.
 */
class Entity: public std::enable_shared_from_this<Entity> {
    public:
        virtual ~Entity() = default;
        Entity(Color color = BLACK, Vec2 pos = Vec2(0,0), int health = 3);
        bool alive = true;

        std::string name = "Generic";
        Color disp;
        Vec2 pos;
        int health;

        Inventory inventory;

        virtual void damage(int value);
        virtual Action takeTurn(Map* map);
        int attack();
};

#endif // ENTITY_HPP
