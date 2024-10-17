#include "inventory.hpp"

// Store the given item
void Inventory::store(std::shared_ptr<Item> item) {
    this->items.push_back(item);
}

// Take out item from given index
std::shared_ptr<Item> Inventory::drop(int itemIndex) {
    std::shared_ptr<Item> temp = this->items.at(itemIndex);
    std::erase(this->items, temp);
    return temp;
}
