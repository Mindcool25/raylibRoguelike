#include "map.hpp"
#include <iostream>
#include <string>

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

void Map::setEntity(std::shared_ptr<Entity> e) {
    if (auto search = this->tiles.find(e->pos); search !=this->tiles.end()) {
        Tile* tile = &search->second;
        tile->entity = e;
    }
}

void Map::placeEntity(std::shared_ptr<Entity> e, Vec2 pos) {
    if (auto search = this->tiles.find(pos); search !=this->tiles.end()) {
        Tile* tile = &search->second;
        tile->entity = e;
    }
}

void Map::clearEntity(Vec2 pos) {
    if (auto search = this->tiles.find(pos); search !=this->tiles.end()) {
        Tile* tile = &search->second;
        tile->entity.reset();
    }
}

bool Map::tryMove(Vec2 pos) {
    if (auto search = this->tiles.find(pos); search !=this->tiles.end()) {
        Tile* tile = &search->second;
        return tile->isOpen();
    }
    return false;
}

Tile* Map::getTile(Vec2 pos) {
    if (auto search = this->tiles.find(pos); search !=this->tiles.end()) {
        Tile* tile = &search->second;
        return tile;
    }
    else {
        return nullptr;
    }

}

void Map::runActors() {
    std::vector<std::shared_ptr<Entity>> remove;

    // Check if entity is alive, then move. If dead, add it to a vector to be erased
    for (auto i : actors) {
        if (i->health <= 0) {
            remove.push_back(i);
        } else {
            Vec2 iPos = i->move(this);
            this->getTile(i->pos)->entity = nullptr;
            i->pos = iPos;
            this->getTile(iPos)->entity = i;
        }
    }

    // Remove entity from the tile, then remove it from the actors vector
    for (auto j : remove) {
        this->clearEntity(j->pos);
        std::erase(this->actors, j);
    }
}
