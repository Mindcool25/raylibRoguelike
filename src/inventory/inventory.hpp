#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

#include <memory>
#include <vector>

#include "../item/item.hpp"

class Inventory {
    public:
        std::vector<std::shared_ptr<Item>> items;


        void store(std::shared_ptr<Item> item);
        std::shared_ptr<Item> drop(int itemIndex);
};

#endif // INVENTORY_HPP_
