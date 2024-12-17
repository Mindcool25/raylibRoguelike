#include "scheduler.hpp"

#include <memory>

#include "../game/game.hpp"


// Get all entities running this tick and have them move
void Scheduler::runCurrent(Game* game, Map* map) {
    // Setting the tick to done as default
    bool tickDone = true;

    // Get all enities that need to be ran this tick
    auto range = this->schedule.equal_range(this->tick);
    for ( auto i = range.first; i != range.second; i++ ) {

        // Double check that the tick is correct
        if (i->first == this->tick) {

            // if it is, check if the thing has not moved and is alive
            if (i->second->type == ActionType::none && i->second->e->alive) {

                // If it didn't move, ask it for an action
                i->second = std::make_shared<Action>(i->second->e->takeTurn(map));

                // If the action is valid, run the action and reschedule the entity
                if (i->second->type != ActionType::none) {
                    game->handleAction(i->second);
                    this->scheduleEntity(i->second->e, this->tick + i->second->cost);
                }
                // If the entity fails to move, tell the schedule that it isn't done
                else {
                    tickDone = false;
                }
            }
        }
    }

    // If the tick is done, get all ticks under the current tick and remove it
    // Then move on to next tick.
    if (tickDone) {
        // No memory leak for you
        auto range = this->schedule.lower_bound(this->tick);
        this->schedule.erase(this->schedule.begin(), range);
        this->tick++;
    }
}

// Schedlue an entity
void Scheduler::scheduleEntity(std::shared_ptr<Entity> e, int scheduleTick) {
    // Create a new action cost amount of ticks after current tick
    Action newAction = Action{0, scheduleTick, Vec2(0,0), ActionType::none, e};
    // Add it to the schedule
    this->schedule.insert({newAction.tick, std::make_shared<Action>(newAction)});
}
