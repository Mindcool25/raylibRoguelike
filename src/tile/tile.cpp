#include "tile.hpp"

Tile::Tile(bool walkable, char disp, Color color) {
    this->walkable = walkable;
    this->disp.dispChar = disp;
    this->disp.color = color;
}

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

std::vector<std::shared_ptr<Item>> Tile::getItems() {
    return this->items;
}
