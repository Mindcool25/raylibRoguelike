#include "../entity.hpp"
#include "../../map/map.hpp"
#include "../../utils/vec2.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class PlayerEntity: public Entity {
    public:
        PlayerEntity(Color disp = GREEN, Vec2 pos = Vec2(0,0), int health = 53, std::string name = "Player");

        Action takeTurn(Map* map) override;

        int test();
};

#endif // PLAYER_HPP
