#include "map.hpp"
#include "raylib.h"

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
    this->tiles.insert_or_assign(pos, Tile(false, '#'));
}

void Map::setFloor(Vec2 pos) {
    this->tiles.insert_or_assign(pos, Tile(true, '.'));
}


// TODO: This should be changed eventually to use ASCII rather than
//       colored squares.
void Map::render(int tile_size, Font font) const {
    for (auto t = this->tiles.begin(); t != this->tiles.end(); t++) {
        Tile curr = t->second;
        Disp disp = Disp('.' ,WHITE);
        if (curr.entity != nullptr) {
            disp = curr.entity->disp;
        }
        else {
            disp = curr.disp;
        }
        //DrawRectangle(t->first.x * tile_size, t->first.y * tile_size, tile_size, tile_size, color);
        DrawTextCodepoint(font, disp.dispChar, Vector2(t->first.x * tile_size, t->first.y * tile_size), tile_size, disp.color);
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
