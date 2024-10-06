#include "map.hpp"

Map::~Map() {
}

Map::Map(Vec2 size) {
    this->map_size = size;

    // NOTE: this is where map gen will happen
    for (int i = 0; i < map_size.y; i++) {
        for (int j = 0; j < map_size.x; j ++) {
            if (i == 0 || i == map_size.y - 1) {
                setWall(Vec2(i, j));
            }
            else {
                if (j == 0 || j == map_size.x - 1) {
                    setWall(Vec2(i, j));
                }
                else {
                    if (GetRandomValue(0, 5) == 100) {
                        setWall(Vec2(i, j));
                    } else {
                        setFloor(Vec2(i, j));
                    }
                }
            }
        }
    }
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

void Map::clearEntity(Vec2 pos) {
    Tile* tile = this->getTile(pos);
    if (tile != nullptr) {
        tile->entity.reset();
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
