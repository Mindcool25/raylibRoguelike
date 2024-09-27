#include "scheduler.hpp"
#include <memory>
#include "../game/game.hpp"

#include <iostream>

// TODO: IMPORTANT!
// Right now rescheduling seems to be borked when it comes to same tick things. needs to be fixed


// TODO: Rewrite to use multimap
//       Might need to have this run entity things
//       Maybe have the scheduler return the action
//       then have the map react to that
std::shared_ptr<Entity> Scheduler::getCurrent() {
    return nullptr;
}

void Scheduler::runCurrent(Game* game, Map* map) {
    bool tickDone = true;

    auto range = this->schedule.equal_range(this->tick);

    for (auto i = range.first; i != range.second; ++i) {
        Action eAction = i->second->e->takeTurn(map);
        std::cout << eAction.cost << std::endl;
        eAction.e = i->second->e;
        std::cout << eAction.target.x << ", " << eAction.target.y << std::endl;
        if (eAction.type != ActionType::none) {
            game->handleAction(eAction);
            this->scheduleEvent(Action{eAction.cost, this->tick, Vec2(0,0), ActionType::none, i->second->e});
        }
        else {
            tickDone = false;
        }
    }
    if (tickDone) {
        this->tick ++;
    }

}

void Scheduler::scheduleEvent(Action action) {
    if (schedule.contains(this->tick + action.cost)) {
        std::cout << "smack" << std::endl;
    }
    // Create a new action cost amount of ticks after current tick
    Action newAction = Action{0, this->tick + action.cost, Vec2(0,0), ActionType::none, action.e};
    // Add it to the schedule
    this->schedule.insert({newAction.tick, std::make_shared<Action>(newAction)});
}

void Scheduler::removeEntity(std::shared_ptr<Entity> e) {
    std::cout << "why is this ran???" << std::endl;
    for ( auto i = this->schedule.begin(); i != this->schedule.end(); i++ ) {
        if (i->first > this->tick) {
            if (i->second->e == e) {
                this->schedule.erase(i);
            }
        }
    }
}
