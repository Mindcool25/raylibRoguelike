#ifndef SCHEDULER_HPP_
#define SCHEDULER_HPP_

#include "../entity/entity.hpp"
#include "../utils/action.hpp"

#include <map>
#include <memory>
#include <vector>

class Game;

class Scheduler {
    public:
        int tick = 0;

        std::shared_ptr<Entity> getCurrent();
        void runCurrent(Game* game, Map* map);

        void scheduleEntity(std::shared_ptr<Entity> e, int scheduleTick);
        void removeEntity(std::shared_ptr<Entity> e);

    private:
        std::multimap<int, std::shared_ptr<Action>> schedule;

        std::vector<std::shared_ptr<Action>> tickActions;

        void getCurrentActions();

        std::shared_ptr<Action> currentAction;

};


#endif // SCHEDULER_HPP_
