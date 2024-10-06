#include "raylib.h"
#include "map/map.hpp"
#include "game/game.hpp"
#include "utils/action.hpp"
#include "utils/vec2.hpp"
#include "entity/entity.hpp"
#include "entity/player/player.hpp"

#include <memory>
#include <iostream>

// DONE: Rewrite most things to work with a main game object
// TODO: scheduling should use a multimap to allow multiple things happening on one tick.
// TODO: Rewrite scheduling and entity turns
// TODO: Implement items, inventories
// TODO: Change rendering to be done with ASCII rather than colored squares.
// TODO: Refactor everything, standardize var names and import patterns.

void draw() {
    ClearBackground(BLACK);
    return;
}

void update() {
    return;
}

int main() {
    Game game;
    /*
    std::shared_ptr<Entity> enemy = std::make_shared<Entity>(Entity(BLACK, Vec2(2,5), 12));
    std::shared_ptr<Entity> enemy2 = std::make_shared<Entity>(Entity(PINK, Vec2(2,2), 10));
    std::shared_ptr<Entity> player = std::make_shared<PlayerEntity>(PlayerEntity(GREEN, Vec2(2,3), 130));
    game.entities.push_back(enemy);
    game.entities.push_back(enemy2);
    game.entities.push_back(player);

    game.map.setEntity(enemy);
    game.map.setEntity(enemy2);
    game.map.setEntity(player);

    Action playerAct = Action{10, 0, Vec2(0,0), ActionType::none, player};
    Action entityAct = Action{3, 0, Vec2(0,0), ActionType::none, enemy};
    Action entityAct2 = Action{3, 0, Vec2(0,0), ActionType::none, enemy2};

    game.schedule.scheduleEntity(player, 1);
    game.schedule.scheduleEntity(enemy, 3);
    game.schedule.scheduleEntity(enemy2, 3);

    player.reset();
    enemy.reset();
    enemy2.reset();
    */

    for (int i = 0; i < 200; i++) {
        std::shared_ptr<Entity> enemy = std::make_shared<Entity>(Entity(ColorFromHSV(GetRandomValue(0, 355), 100, 100), Vec2(GetRandomValue(1, 90),GetRandomValue(1, 90)), 12));
        game.entities.push_back(enemy);
        game.map.setEntity(enemy);
        game.schedule.scheduleEntity(enemy, GetRandomValue(1, 30));
        std::cout << "Created entity " << i << " out of 100" << std::endl;
    }

    game.gameLoop();

    return 0;
}
