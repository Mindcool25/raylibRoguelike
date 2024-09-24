#ifndef ACTION_HPP_
#define ACTION_HPP_

#include <memory>
#include "vec2.hpp"

class Entity;

enum ActionType {
    none,
    wait,
    move,
    attack,
};

// TODO: Brainstorm how to save this stuff
struct Action {
    int cost;
    int tick;
    Vec2 target;
    ActionType type;
    std::shared_ptr<Entity> e;
};

#endif // ACTION_HPP_
