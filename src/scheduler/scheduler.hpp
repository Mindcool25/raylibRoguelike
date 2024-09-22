#ifndef SCHEDULER_HPP_
#define SCHEDULER_HPP_

#include "../entity/entity.hpp"
#include <map>
#include <memory>

class Scheduler {
    public:
        int tick = 0;

        std::shared_ptr<Entity> getCurrent();

        void scheduleEvent(int tick, std::shared_ptr<Entity> e);

    private:
        std::map<int, std::shared_ptr<Entity>> schedule;
};


#endif // SCHEDULER_HPP_
