#include "cave.hpp"
#include "raylib.h"

#include <bits/stdc++.h>

void Cave::generate(Map* map, int wall_rule, int floor_rule, int iter) {
    srand(time(0));
    SetRandomSeed(rand());

    int x_mid = map->map_size.x / 2;
    int y_mid = map->map_size.y / 2;
    Vec2 midpoint = Vec2(x_mid, y_mid);

    map->setFloor(midpoint);


    for (int i = 0; i < iter * 500; i++) {
        Vec2 randPos = Vec2(GetRandomValue(0, map->map_size.x), GetRandomValue(0, map->map_size.y));
        if (map->getTile(randPos)) {
            map->setWall(randPos);
        }
        else {
            map->setFloor(randPos);
        }
    }

    return;
}
