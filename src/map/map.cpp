#include "map.hpp"
#include <iostream>

Map::~Map() {
}

Map::Map(Vec2 size) {
    this->map_size = size;
}

Map::Map() {
    this->map_size = Vec2(10, 10);
}

bool Map::isWall(Vec2 pos) const {
    return (this->tiles.contains(pos) && !this->tiles.at(pos).walkable);
}

void Map::setWall(Vec2 pos) {
    Tile newWall;
    newWall.walkable = false;
    this->tiles.insert_or_assign(pos, newWall);
};

void Map::setFloor(Vec2 pos) {
    Tile newFloor;
    newFloor.walkable = true;
    this->tiles.insert_or_assign(pos, newFloor);
}


void Map::render(int tile_size) const {
    for (auto t = this->tiles.begin(); t != this->tiles.end(); t++) {
        Tile curr = t->second;
        Color color = WHITE;
        if (curr.entity != nullptr) {
            color = curr.entity->disp;
            std::cout << "E";
        }
        else if (!curr.walkable) {
            color = RED;
        }
        else if (curr.walkable) {
            color = BLUE;
        }
        DrawRectangle(t->first.x * tile_size, t->first.y * tile_size, tile_size, tile_size, color);
    }
}

void Map::setEntity(Entity* e) {
    if (auto search = this->tiles.find(e->pos); search !=this->tiles.end()) {
        Tile tile = search->second;
        tile.entity = e;
    }
}

bool Map::tryMove(Vec2 pos) {
    if (auto search = this->tiles.find(pos); search !=this->tiles.end()) {
        Tile tile = search->second;
        return tile.isOpen();
    }
    return true;
}
