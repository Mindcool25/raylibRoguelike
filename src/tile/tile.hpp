#ifndef TILE_HPP_
#define TILE_HPP_

#include <vector>
#include <memory>

#include "../entity/entity.hpp"
#include "../item/item.hpp"
#include "raylib.h"

enum Occupant {
    empty,
    entity,
    wall,
};

class Tile {
    public:
        bool walkable;
        std::shared_ptr<Entity> entity = nullptr;
        std::vector<std::shared_ptr<Item>> items;

        bool isOpen();
        Occupant getOccupant();
};

#endif // TILE_HPP_
