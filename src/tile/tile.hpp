#ifndef TILE_HPP_
#define TILE_HPP_

#include <vector>
#include <memory>

#include "../entity/entity.hpp"
#include "raylib.h"

class Tile {
    public:
        bool walkable;
        std::shared_ptr<Entity> entity = nullptr;
        std::vector<int> items;

        bool isOpen();
};

#endif // TILE_HPP_
