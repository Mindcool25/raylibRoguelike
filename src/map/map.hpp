#ifndef MAP_HPP
#define MAP_HPP

#include <unordered_map>
#include "../utils/vec2.hpp"
#include "../tile/tile.hpp"
#include "../entity/entity.hpp"


class Map {
    public:
        Vec2 map_size = Vec2(1, 1);

        Map(Vec2 size);
        Map();
        ~Map();

        void setEntity(Entity* e);

        void setWall(Vec2 pos);
        void setFloor(Vec2 pos);

        bool isWall(Vec2 pos) const;

        bool tryMove(Vec2 Pos);

        void render(int tile_size) const;

    protected:
        std::unordered_map<Vec2, Tile, VecHash> tiles;
};

#endif
