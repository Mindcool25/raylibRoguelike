#include "../entity.hpp"

#include "../../map/map.hpp"
#include "../../utils/vec2.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class PlayerEntity: public Entity {
    public:
        // Constructor
        PlayerEntity(Disp disp = Disp{'@', WHITE}, Vec2 pos = Vec2(0,0), int health = 53, std::string name = "Player");

        // Take a turn
        Action takeTurn(Map* map) override;

        // Inventory management
        void checkInventory();
        void addInventory(Map* map);
        void dropItem(Map* map);

        Inventory inventory;
};

#endif // PLAYER_HPP
