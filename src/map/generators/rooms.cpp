#include "rooms.hpp"

#include <bits/stdc++.h>
#include <iostream>

void Rooms::generate(Map* map, int rooms) {
    srand(time(0));
    SetRandomSeed(rand());
    for(int i = 0; i < rooms; i++) {
        Vec2 roomPos = Vec2::randomVec(0, map->map_size.x, 0, map->map_size.y);
        std::cout << roomPos.x << " " << roomPos.y << std::endl;
        makeRoom(map, roomPos, rand() % 10 + 5);
    }
}

void Rooms::makeRoom(Map* map, Vec2 pos, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j ++) {
            if (i == 0 || i == size - 1) {
                map->setWall(Vec2(pos.x + i, pos.y + j));
            }
            else {
                if (j == 0 || j == size - 1) {
                    map->setWall(Vec2(pos.x + i, pos.y + j));
                }
                else {
                    map->setFloor(Vec2(pos.x + i, pos.y + j));
                }
            }
        }
    }

}
