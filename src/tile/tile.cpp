#include "tile.hpp"

Tile::Tile(Disp disp, bool walkable) {
    this->walkable = walkable;
    this->disp = disp;
}

// TODO: This is probably obsolete due to getOccupant
bool Tile::isOpen() {
    return walkable && (entity == nullptr);
}

// Get current occupant of a tile
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
