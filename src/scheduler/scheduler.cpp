#include "scheduler.hpp"
#include <memory>
#include "../game/game.hpp"

void Scheduler::runCurrent(Game* game, Map* map) {
    bool tickDone = true;

    auto range = this->schedule.equal_range(this->tick);
    for ( auto i = range.first; i != range.second; i++ ) {
        if (i->first == this->tick) {
            if (i->second->type == ActionType::none && i->second->e->alive) {
                i->second = std::make_shared<Action>(i->second->e->takeTurn(map));
                if (i->second->type != ActionType::none) {
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
        // No memory leak for you
        auto range = this->schedule.lower_bound(this->tick);
        this->schedule.erase(this->schedule.begin(), range);
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
}
