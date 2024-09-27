#include "scheduler.hpp"
#include <memory>
#include <iostream>
#include "../game/game.hpp"


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
    auto actions = this->schedule.equal_range(this->tick);
    for (auto action = actions.first; action != actions.second; action++) {
        // Ask the entity what it wants to do, set the action to that.
        action->second = std::make_shared<Action>(action->second->e->move(map));

        // If the action was actually set, run the action and schedule next action.
        if (action->second->type != ActionType::none) {
            game->handleAction(action->second);
            this->scheduleEvent(action->second);
        }

        // If not, not all entities have gone. Iterate again on next frame.
        else {
            turnFinished = false;
        }
    }

    // If all entites have gone, continue to next tick.
    if (turnFinished) {
        this->tick++;
    }
}

void Scheduler::scheduleEvent(std::shared_ptr<Action> action) {
    // Create a new action cost amount of ticks after current tick
    Action newAction = Action{0, this->tick + action->cost, Vec2(0,0), ActionType::none, action->e};
    // Add it to the schedule
    this->schedule.insert({newAction.tick, std::make_shared<Action>(newAction)});
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
