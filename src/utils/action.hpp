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
    int cost = 0;
    int tick = 0;
    Vec2 target = Vec2{0, 0};
    ActionType type = ActionType::none;
    std::shared_ptr<Entity> e = nullptr;
};

#endif // ACTION_HPP_
