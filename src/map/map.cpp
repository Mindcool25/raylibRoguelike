#include "map.hpp"
#include <iostream>
#include <string>

Map::~Map() {
}

Map::Map(Vec2 size) {
    this->map_size = size;
}

void Map::setWall(Vec2 pos) {
    Tile newWall;
    newWall.walkable = false;
    this->tiles.insert_or_assign(pos, newWall);
};

void Map::setFloor(Vec2 pos) {
    Tile newFloor;
    newFloor.walkable = true;
    this->tiles.insert_or_assign(pos, newFloor);}


// TODO: This should be changed eventually to use ASCII rather than
//       colored squares.
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
    Tile* tile = this->getTile(e->pos);
    if (tile != nullptr) {
        tile->entity = e;
    }
}

void Map::placeEntity(std::shared_ptr<Entity> e, Vec2 pos) {
    Tile* tile = this->getTile(pos);
    if (tile != nullptr) {
        tile->entity = e;
    }
}

void Map::clearEntity(Vec2 pos) {
    Tile* tile = this->getTile(pos);
    if (tile != nullptr) {
        tile->entity.reset();
    }
}

bool Map::tryMove(Vec2 pos) {
    Tile* tile = this->getTile(pos);
    if (tile != nullptr) {
        return tile->isOpen();
    }
    else {
        return false;
    }
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

// TODO: Make sure to rewrite this with the main game object
//       Probably make the game object control the entity turns
//       Map doesn't need to bother with entities
void Map::runActors() {
    std::vector<std::shared_ptr<Entity>> remove;

    // Check if entity is alive, then move. If dead, add it to a vector to be erased
    for (auto i : actors) {
        if (this->schedule.getCurrent() == i) {
            if (i->health <= 0) {
                remove.push_back(i);
                i.reset();
            } else {
                Vec2 iPos = i->move(this);
                // Check if the entity actually moved, if it did, move on to next tick
                if (iPos != i->pos) {
                    this->getTile(i->pos)->entity = nullptr;
                    i->pos = iPos;
                    this->getTile(iPos)->entity = i;
                    this->schedule.tick += 1;
                }
            }
        }
    }

    // Remove entity from the tile, then remove it from the actors vector
    for (auto j : remove) {
        this->clearEntity(j->pos);
        this->schedule.removeEntity(j);
        std::erase(this->actors, j);
    }
}
