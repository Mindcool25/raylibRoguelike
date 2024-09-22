#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <vector>
#include <unordered_map>
#include "../utils/vec2.hpp"
#include "../tile/tile.hpp"
#include "../entity/entity.hpp"
#include "../scheduler/scheduler.hpp"
#include "raylib.h"


class Map {
    public:
        Map(Vec2 size = Vec2(10,10));
        ~Map();

        Vec2 map_size = Vec2(1, 1);


        Scheduler schedule;
        std::vector<std::shared_ptr<Entity>> actors;

        void runActors();
        void setEntity(std::shared_ptr<Entity> e);
        void placeEntity(std::shared_ptr<Entity> e, Vec2 pos);
        void clearEntity(Vec2 pos);

        Tile* getTile(Vec2 pos);
        void hitEntity(Vec2 pos, int val);

        void setWall(Vec2 pos);
        void setFloor(Vec2 pos);

        bool isWall(Vec2 pos) const;

        bool tryMove(Vec2 Pos);

        void render(int tile_size) const;

    protected:
        std::unordered_map<Vec2, Tile, VecHash> tiles;
};

#endif
