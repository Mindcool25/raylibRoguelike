#include "scheduler.hpp"
#include <memory>
#include "../game/game.hpp"

#include <iostream>

// DONE: Fix scheduling

// DONE?: Rewrite to use multimap
//       Might need to have this run entity things
//       Maybe have the scheduler return the action
//       then have the map react to that

// TODO: figure out why sometimes entities will just take a bunch of turns
std::shared_ptr<Entity> Scheduler::getCurrent() {
    return nullptr;
}

void Scheduler::runCurrent(Game* game, Map* map) {
    bool tickDone = true;

    // Get the entities scheduled to go on this tick and iterate over them
    auto range = this->schedule.equal_range(this->tick);
    for (auto i = range.first; i != range.second; ++i) {
        // Make sure the entity hasn't already gone
        if (i->second->type == ActionType::none) {
            // Get the entity's action, if it doesn't do anything make sure to try again next frame
            Action eAction = i->second->e->takeTurn(map);
            if (eAction.type == ActionType::none) {
                tickDone = false;
            }

            // Otherwise handle the action, schedule the next one, then make this action as done.
            else {
                game->handleAction(eAction);
                this->scheduleEvent(Action{eAction.cost, 0, Vec2(0,0),ActionType::none, i->second->e});
                i->second = std::make_shared<Action>(eAction);
            }
        }
    }
    if (tickDone) {
        std::cout << "Tick done" << std::endl;
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
    for ( auto i = this->schedule.begin(); i != this->schedule.end(); i++ ) {
        if (i->first > this->tick) {
            if (i->second->e == e) {
                this->schedule.erase(i);
            }
        }
    }
}
