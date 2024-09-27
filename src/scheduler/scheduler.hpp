#ifndef SCHEDULER_HPP_
#define SCHEDULER_HPP_

#include "../entity/entity.hpp"
#include "../utils/action.hpp"
#include <map>
#include <memory>

// Forward decleration go brrr
class Game;

class Scheduler {
    public:
        int tick = 0;

        std::shared_ptr<Entity> getCurrent();
        void runCurrent(Game* game, Map* map);

        void scheduleEvent(Action action);
        void removeEntity(std::shared_ptr<Entity> e);

    private:
        std::multimap<int, std::shared_ptr<Action>> schedule;
};


#endif // SCHEDULER_HPP_
