#include "scheduler.hpp"
#include <memory>

std::shared_ptr<Entity> Scheduler::getCurrent() {
    if (schedule.contains(tick)) {
        return schedule.find(tick)->second;
    }
    else {
        this->tick++;
        return nullptr;
    }
}

void Scheduler::scheduleEvent(int tick, std::shared_ptr<Entity> e) {
    this->schedule[tick] = e;
}
