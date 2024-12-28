#ifndef ROOMS_HPP
#define ROOMS_HPP

#include "../map.hpp"

class Rooms {
    public:
        static void generate(Map* map, int rooms = 5);
        static void makeRoom(Map* map, Vec2 pos, int size);
        static void makeHall();
};

#endif 
