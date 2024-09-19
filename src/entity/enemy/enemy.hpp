#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include "../entity.hpp"
#include "../../map/map.hpp"

class EnemyEntity: public Entity {
    public:
        ~EnemyEntity() = default;
        EnemyEntity(Color disp = PURPLE, Vec2 pos = Vec2(0,0), int health = 10);

        Vec2 move(Map* map) override;
};

#endif // ENEMY_HPP_
