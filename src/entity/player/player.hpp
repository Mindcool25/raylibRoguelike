#include "../entity.hpp"
#include "../../map/map.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class PlayerEntity: public Entity {
    public:
        PlayerEntity(Color disp = GREEN, Vec2 pos = Vec2(0,0), int health = 53);

        void move(Map* map) override;
};

#endif // PLAYER_HPP
