#include "tile.hpp"
#include <iostream>

bool Tile::isOpen() {
    return walkable && (entity == nullptr);
}
