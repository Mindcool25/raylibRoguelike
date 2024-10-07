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
// DONE: scheduling should use a multimap to allow multiple things happening on one tick.
// DONE: Rewrite scheduling and entity turns
// DONE: Reimplement attacking
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
    std::shared_ptr<Entity> player = std::make_shared<PlayerEntity>(PlayerEntity(GREEN, Vec2(2,3), 130));
    game.entities.push_back(player);

    game.map.setEntity(player);

    game.schedule.scheduleEntity(player, 1);

    player.reset();

    for (int i = 0; i < 200; i++) {
        std::shared_ptr<Entity> enemy = std::make_shared<Entity>(Entity(ColorFromHSV(GetRandomValue(0, 355), 100, 100), Vec2(GetRandomValue(1, 90),GetRandomValue(1, 90)), 12));
        game.entities.push_back(enemy);
        game.map.setEntity(enemy);
        game.schedule.scheduleEntity(enemy, GetRandomValue(1, 30));
    }

    game.gameLoop();

    return 0;
}
