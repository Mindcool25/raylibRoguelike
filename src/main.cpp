#include "raylib.h"
#include "game/game.hpp"
#include "utils/vec2.hpp"
#include "entity/entity.hpp"
#include "entity/player/player.hpp"

#include <memory>

// DONE: Rewrite most things to work with a main game object
// DONE: scheduling should use a multimap to allow multiple things happening on one tick.
// DONE: Rewrite scheduling and entity turns
// DONE: Reimplement attacking
// DONE (kinda): Implement items, inventories
// DONE: Change rendering to be done with ASCII rather than colored squares.
// TODO: Refactor everything, standardize var names and import patterns.
// TODO: Fully implement items

void draw() {
    ClearBackground(BLACK);
    return;
}

void update() {
    return;
}

int main() {
    Game game;
    std::shared_ptr<Entity> player = std::make_shared<PlayerEntity>(PlayerEntity(Disp{'@', WHITE}, Vec2(2,3), 130));
    game.entities.push_back(player);

    game.map.setEntity(player);

    game.schedule.scheduleEntity(player, 1);

    player.reset();

    std::shared_ptr<Item> item = std::make_shared<Item>(Item());
    game.map.addItem(Vec2{5, 5}, item);
    item.reset();


    for (int i = 0; i < 5; i++) {
        Color entityColor = ColorFromHSV(GetRandomValue(0, 355), 100, 100);
        char entityChar = 'E';
        std::shared_ptr<Entity> enemy = std::make_shared<Entity>(Entity(Disp{entityChar, entityColor}, Vec2(GetRandomValue(1, 20),GetRandomValue(1, 20)), 12));
        game.entities.push_back(enemy);
        game.map.setEntity(enemy);
        game.schedule.scheduleEntity(enemy, GetRandomValue(1, 30));
    }

    game.gameLoop();

    return 0;
}
