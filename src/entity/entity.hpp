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
        // Deconstructor
        virtual ~Entity() = default;

        // Constructor
        Entity(Disp disp = Disp{'e', PINK}, Vec2 pos = Vec2(0,0), int health = 3);

        // Base variables
        std::string name;
        bool alive = true;
        int health;
        Disp disp;
        Vec2 pos;

        // inventory
        Inventory inventory;

        // Default damage, attack, and take turn function for entities
        virtual Action takeTurn(Map* map);
        virtual void damage(int value);
        int attack();
};

#endif // ENTITY_HPP
