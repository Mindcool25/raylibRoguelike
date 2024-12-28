#ifndef CAVE_HPP
#define CAVE_HPP

#include "../map.hpp"

class Cave {
    public:
        static void generate(Map* map, int iter = 1, int wall_rule = 4, int floor_rule = 3);
};

#endif
