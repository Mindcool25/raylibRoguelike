#include "raylib.h"
#include "map/map.hpp"
#include "game/game.hpp"
#include "utils/vec2.hpp"
#include "entity/entity.hpp"
#include "entity/player/player.hpp"
#include "entity/enemy/enemy.hpp"

#include <iostream>
#include <memory>

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
    std::shared_ptr<Entity> enemy = std::make_shared<Entity>(Entity(PINK, Vec2(2,2), 10));
    std::shared_ptr<Entity> player = std::make_shared<PlayerEntity>(PlayerEntity(GREEN, Vec2(2,3), 13));
    game.entities.push_back(enemy);
    game.entities.push_back(player);

    game.map.setEntity(enemy);
    game.map.setEntity(player);

    for (int i = 0; i < 100; i++) {
        if (i%2 == 0) {
            game.schedule.scheduleEvent(i, player);
        }
        else {
            game.schedule.scheduleEvent(i, enemy);
        }
    }

    player.reset();
    enemy.reset();

    game.gameLoop();

    return 0;
}
