#include "inventory.hpp"

void Inventory::pickUp(std::shared_ptr<Item> item) {
    this->items.push_back(item);
}

std::shared_ptr<Item> Inventory::drop(int itemIndex) {
    std::shared_ptr<Item> temp = this->items.at(itemIndex);
    std::erase(this->items, temp);
    return temp;
}
