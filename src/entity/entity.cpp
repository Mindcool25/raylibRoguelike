#include "entity.hpp"

#include "raylib.h"

#include "../tile/tile.hpp"
#include "../map/map.hpp"

#include <iostream>
/**
 * Entity constructor
 */
Entity::Entity(Disp disp,  Vec2 pos, int health) {
    this->disp = disp;
    this->pos = pos;
    this->health = health;
}

// NOTE: This will need some redoing, mainly with taking damage.
//       Possibly have a more specific damage input, and a list of
//       effects to apply.
void Entity::damage(int value){
    this->health -= value;
    if (this->health <=0) {
        std::cout << "DEAD" << std::endl;
        this->alive = false;
    }
}

int Entity::attack() {
    int value = this->health / 5;
    return value;
}

Action Entity::takeTurn(Map *map) {
    int cost = 3;
    int tick = 0;
    Vec2 target = Vec2(0,0);
    ActionType type = ActionType::none;

    Vec2 mov = Vec2(0,0);
    switch(GetRandomValue(0, 3)) {
        // NSEW movement
        case 0: mov = Vec2(0, 1); break;
        case 1: mov = Vec2(0, -1); break;
        case 2: mov = Vec2(1, 0); break;
        case 3: mov = Vec2(-1, 0); break;
    }
    if (mov != Vec2(0,0)) {
        Vec2 newPos = mov + this->pos;
        if (Tile* curr = map->getTile(newPos); curr != nullptr)  {
            switch (curr->getOccupant()) {
                case Occupant::empty:
                    target = newPos;
                    type = ActionType::move;
                    break;
                case Occupant::entity:
                    target = newPos;
                    type = ActionType::attack;
                    break;
                case Occupant::wall:
                    target = newPos;
                    type = ActionType::none;
                    break;
            }
        }
    }
    return Action{cost, tick, target, type, shared_from_this()};
}
