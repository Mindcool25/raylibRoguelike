#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>

enum ItemType {
    trash,
    weapon,
    consumable,
};

class Item {
    public:
        ItemType type;
        std::string name;
        void use();
};


#endif // ITEM_HPP_
