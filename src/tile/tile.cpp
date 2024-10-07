#include "tile.hpp"
#include <iostream>

bool Tile::isOpen() {
    return walkable && (entity == nullptr);
}

Occupant Tile::getOccupant() {
    if (this->entity != nullptr) {
        return Occupant::entity;
    }
    else if (!this->walkable) {
        return Occupant::wall;
    }
    else {
        return Occupant::empty;
    }
}
