#include "scheduler.hpp"
#include <memory>
#include "../game/game.hpp"

#include <iostream>


// TODO: Rewrite to use multimap
//       Might need to have this run entity things
//       Maybe have the scheduler return the action
//       then have the map react to that
std::shared_ptr<Entity> Scheduler::getCurrent() {
    return nullptr;
}

void Scheduler::runCurrent(Game* game, Map* map) {
    // Variable to check if all entities have gone
    bool turnFinished = true;

    // Get all actions schedule for current tick and iterate over them
    int times = 0;
    auto actions = this->schedule.equal_range(this->tick);
    for (auto action = actions.first; action != actions.second; action++) {
        // Ask the entity what it wants to do, set the action to that.
        times ++;
        Action a = action->second->e->takeTurn(map);
        action->second->cost = a.cost;
        action->second->type = a.type;
        action->second->target = a.target;

        // If the action was actually set, run the action and schedule next action.
        if (action->second->type != ActionType::none && action->second->tick == this->tick) {
            game->handleAction(action->second);
            this->scheduleEvent(action->second);
        }

        // If not, not all entities have gone. Iterate again on next frame.
        else {
            turnFinished = false;
        }
    }
    if (times > 1) {
    }
    // If all entites have gone, continue to next tick.
    if (turnFinished) {
        this->tick++;
    }
    else {
    }
}

void Scheduler::scheduleEvent(std::shared_ptr<Action> action) {
    if (this->tick > this->tick + action->cost) {
        std::cout << "huh? " << action->type << std::endl;
    }
    if (schedule.contains(this->tick + action->cost)) {
        std::cout << "smack" << std::endl;
    }
    // Create a new action cost amount of ticks after current tick
    Action newAction = Action{0, this->tick + action->cost, Vec2(0,0), ActionType::none, action->e};
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
