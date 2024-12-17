#include "inventory.hpp"

// Store the given item
void Inventory::store(std::shared_ptr<Item> item) {
    this->items.push_back(item);
}

// Take out item from given index
std::shared_ptr<Item> Inventory::drop(int itemIndex) {
    if (this->items.size() < itemIndex + 1) {
        return nullptr;
    }
    std::shared_ptr<Item> temp = this->items.at(itemIndex);
    std::erase(this->items, this->items.at(itemIndex));
    return temp;
}
