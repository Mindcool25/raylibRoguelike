#include "tile.hpp"

bool Tile::isOpen() {
    return walkable && !(entity == nullptr);
}
