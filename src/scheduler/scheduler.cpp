#include "scheduler.hpp"
#include <memory>
#include "../game/game.hpp"

#include <iostream>

// DONE: Fix scheduling

// DONE?: Rewrite to use multimap
//       Might need to have this run entity things
//       Maybe have the scheduler return the action
//       then have the map react to that
//
void Scheduler::runCurrent(Game* game, Map* map) {
    bool tickDone = true;

    auto range = this->schedule.equal_range(this->tick);
    for ( auto i = range.first; i != range.second; i++ ) {
        if (i->first == this->tick) {
            if (i->second->type == ActionType::none) {
                i->second = std::make_shared<Action>(i->second->e->takeTurn(map));
                if (i->second->type != ActionType::none) {
                    std::cout << "Entity of type " << i->second->e->name << " taking turn" << std::endl;
                    game->handleAction(i->second);
                    this->scheduleEntity(i->second->e, this->tick + i->second->cost);
                }
                else {
                    tickDone = false;
                }
            }
        }
    }

    if (tickDone) {
        std::cout << "Tick " << this->tick << " done ------------------------" << std::endl;
        this->tick++;
    }

}

void Scheduler::scheduleEntity(std::shared_ptr<Entity> e, int scheduleTick) {
    // Create a new action cost amount of ticks after current tick
    Action newAction = Action{0, scheduleTick, Vec2(0,0), ActionType::none, e};
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
