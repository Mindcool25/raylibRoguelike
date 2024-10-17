#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include "../entity.hpp"

class EnemyEntity: public Entity {
    public:
        ~EnemyEntity() = default;
        EnemyEntity(Color color = PURPLE, char disp = 'E', Vec2 pos = Vec2(0,0), int health = 10);
};

#endif // ENEMY_HPP_
