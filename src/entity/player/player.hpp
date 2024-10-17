#include "../entity.hpp"
#include "../../utils/vec2.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class PlayerEntity: public Entity {
    public:
        PlayerEntity(Color color = GREEN, Vec2 pos = Vec2(0,0), int health = 53, std::string name = "Player", char disp = '@');

        Action takeTurn(Map* map) override;

        void checkInventory();
        void addInventory();

        Inventory inventory;
};

#endif // PLAYER_HPP
