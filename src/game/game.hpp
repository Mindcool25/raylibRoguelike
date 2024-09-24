#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <memory>

#include "raylib.h"

#include "../map/map.hpp"
#include "../entity/entity.hpp"
#include "../scheduler/scheduler.hpp"

class Game {
    public:
        Game();

        Map map;
        Scheduler schedule;
        std::vector<std::shared_ptr<Entity>> entities;

        void render();
        void gameLoop();
        void runEntities();

        void moveEntity();
};

#endif // GAME_HPP_
