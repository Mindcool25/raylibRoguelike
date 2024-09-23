#include "scheduler.hpp"
#include <memory>
#include <iostream>

// FIXME: This really needs to be rewritten
//        That being said, moving over to having a
//        main game object will probably make it easier.
//        Really the same with the rest of this
std::shared_ptr<Entity> Scheduler::getCurrent() {
    if (schedule.contains(tick)) {
        std::shared_ptr<Entity> e = schedule.find(tick)->second;
        if (e->health <= 0) {
            std::cout << "WHOAH HEY" << std::endl;
            this->tick++;
            return e;
        }
        return e;
    }
    else {
        this->tick++;
        return nullptr;
    }
}

void Scheduler::scheduleEvent(int tick, std::shared_ptr<Entity> e) {
    this->schedule[tick] = e;
}

void Scheduler::removeEntity(std::shared_ptr<Entity> e) {
    for ( auto i = this->schedule.begin(); i != this->schedule.end(); i++ ) {
        if (i->first > this->tick) {
            if (i->second == e) {
                this->schedule.erase(i);
            }
        }
    }
}
