#include "map.hpp"
#include "raylib.h"
#include <memory>

Map::~Map() {
}

Map::Map(Vec2 size) {
    this->map_size = size;

    // NOTE: this is where map gen will happen
    // This is just making a box, can do random walls
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
                    if (GetRandomValue(0, 5) == 100) { // Just change 100 to 0 < x < 5
                        setWall(Vec2(i, j));
                    } else {
                        setFloor(Vec2(i, j));
                    }
                }
            }
        }
    }
}

// Setting a given location to a wall
void Map::setWall(Vec2 pos) {
    this->tiles.insert_or_assign(pos, Tile(Disp{'#', RED}, false));
}

// Setting a given location to a floor
void Map::setFloor(Vec2 pos) {
    this->tiles.insert_or_assign(pos, Tile(Disp{'.', BLUE}, true));
}

// Put an entity in it's intened place
// NOTE: Error checking would be good here, maybe more than just
//       ignoring the entity set if there is already an entity
void Map::setEntity(std::shared_ptr<Entity> e) {
    Tile* tile = this->getTile(e->pos);
    if (tile != nullptr) {
        tile->entity = e;
    }
}

// Clear Entity from given position
void Map::clearEntity(Vec2 pos) {
    Tile* tile = this->getTile(pos);
    if (tile != nullptr) {
        tile->entity.reset();
    }
}

// Set an item down at given position
void Map::addItem(Vec2 pos, std::shared_ptr<Item> item) {
    this->getTile(pos)->items.push_back(item);
}



// Render game world in ascii
// NOTE: This will need to be messed with for alternate fonts/tilesets
void Map::render(int tile_size, Font font) const {
    for (auto t = this->tiles.begin(); t != this->tiles.end(); t++) {
        Tile curr = t->second;
        Disp disp = Disp{'.' ,WHITE};

        // Display entity if it exists
        if (curr.entity != nullptr) {
            disp = curr.entity->disp;
        }

        // Display item if it exists and entity does not
        else if (!curr.items.empty()) {
            disp = curr.items.back()->disp;
        }

        // Otherwise just draw the tile
        else {
            disp = curr.disp;
        }
        // Old rectangle drawing
        //DrawRectangle(t->first.x * tile_size, t->first.y * tile_size, tile_size, tile_size, color);
        DrawTextCodepoint(font, disp.dispChar, Vector2(t->first.x * tile_size, t->first.y * tile_size), tile_size, disp.color);
    }
}


// Get a pointer to the tile at position, nullptr if it doesn't exist
Tile* Map::getTile(Vec2 pos) {
    if (auto search = this->tiles.find(pos); search !=this->tiles.end()) {
        Tile* tile = &search->second;
        return tile;
    }
    else {
        return nullptr;
    }

}
