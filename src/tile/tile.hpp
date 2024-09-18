#ifndef TILE_HPP_
#define TILE_HPP_

#include <vector>

#include "../entity/entity.hpp"

class Tile {
    public:
        bool walkable;
        Entity* entity = nullptr;
        std::vector<int> items;

        bool isOpen();
};

#endif // TILE_HPP_
