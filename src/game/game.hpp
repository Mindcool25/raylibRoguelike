#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <memory>

#include "raylib.h"

#include "../map/map.hpp"
#include "../entity/entity.hpp"
#include "../scheduler/scheduler.hpp"
/* Game
 * Manages game map, schedule, and entities as
 * well as rendering and running the game loop
 */

class Game {
    public:
        Game();

        Map map;
        Scheduler schedule;
        std::vector<std::shared_ptr<Entity>> entities;

        void render();
        void gameLoop();
        void runEntities();

        void handleAction(std::shared_ptr<Action> action);

        void moveEntity();
};

#endif // GAME_HPP_
