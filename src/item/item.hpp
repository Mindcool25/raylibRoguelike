#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "../utils/disp.hpp"

#include <string>

enum ItemType {
    trash,
    weapon,
    consumable,
};

class Item {
    public:
        Item(Disp disp = Disp{'%', PURPLE}, ItemType type = ItemType::trash, std::string name = "trash Item");

        std::string name;
        ItemType type;
        Disp disp;

        // TODO: Implement this
        void use();
};


#endif // ITEM_HPP_
