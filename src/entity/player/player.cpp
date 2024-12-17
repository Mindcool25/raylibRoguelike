#include "player.hpp"
#include "raylib.h"

#include <iostream>

// TODO: rewrite input to call a function rather than run code inline

PlayerEntity::PlayerEntity(Disp disp, Vec2 pos, int health, std::string name) {
    this->disp = disp;
    this->pos = pos;
    this->health = health;
    this->name = name;
}

Action PlayerEntity::takeTurn(Map* map) {
    // Default action settings
    int cost = 1;
    int tick = 0;
    Vec2 target = Vec2(0,0);
    ActionType type = ActionType::none;

    // Starting position (no move)
    Vec2 mov = Vec2(0,0);
    // Get controls
    switch(GetKeyPressed()) {
        // NSEW movement
        case KEY_J: mov = Vec2(0, 1); break;
        case KEY_K: mov = Vec2(0, -1); break;
        case KEY_L: mov = Vec2(1, 0); break;
        case KEY_H: mov = Vec2(-1, 0); break;

        // Diagnals
        case KEY_Y: mov = Vec2(-1, -1); break;
        case KEY_B: mov = Vec2(-1, 1); break;
        case KEY_N: mov = Vec2(1, 1); break;
        case KEY_U: mov = Vec2(1, -1); break;

        // Wait
        case KEY_PERIOD: type = ActionType::wait; break;

        // Inventory
        case KEY_I: this->checkInventory(); break;
        case KEY_O: this->addInventory(map); break;
        case KEY_D: this->dropItem(map); break;
    }

    // Check if movement was requested, check if tile is valid
    if (mov != Vec2(0,0)) {
        Vec2 newPos = mov + this->pos;
        if (Tile* curr = map->getTile(newPos); curr != nullptr)  {
            switch(curr->getOccupant()) {
                // If it is empty, move there
                case Occupant::empty:
                    target = newPos;
                    type = ActionType::move;
                    break;

                // If there is an entity, attack it
                case Occupant::entity:
                    target = newPos;
                    type = ActionType::attack;
                    break;

                // If there is a wall, this isn't a valid choice
                case Occupant::wall:
                    target = newPos;
                    type = ActionType::none;
                    break;
            }
        }
    }

    return Action{cost, tick, target, type, shared_from_this()};
}

// Print out the player's inventory
void PlayerEntity::checkInventory() {
    std::cout << "INVENTORY: " << std::endl;
    for(auto i : this->inventory.items) {
        std::cout << "Item: " << i->name << std::endl;
    }
}

// Add item from current tile to inventory
void PlayerEntity::addInventory(Map* map) {
    Tile* currTile = map->getTile(this->pos);
    if (!currTile->items.empty()) {
        std::shared_ptr<Item> item = currTile->items.back();
        currTile->items.pop_back();
        this->inventory.store(item);
    }
    else {
        std::cout << "No Items" << std::endl;
    }
}

// Drop item onto the ground
void PlayerEntity::dropItem(Map* map) {
    Tile* currTile = map->getTile(this->pos);
    std::shared_ptr<Item> item = this->inventory.drop(0);
    std::cout << item->name << std::endl;
    if (item != nullptr) {
        currTile->items.push_back(item);
    }
    else {
        std::cout << "No item :)" << std::endl;
    }
}

