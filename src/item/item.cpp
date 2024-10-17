#include "item.hpp"

Item::Item(Disp disp, ItemType type, std::string name) {
    this->disp = disp;
    this->type = type;
    this->name = name;
}
