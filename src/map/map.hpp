#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <unordered_map>

#include "../utils/vec2.hpp"
#include "../tile/tile.hpp"
#include "../entity/entity.hpp"

class Map {
    public:
        Map(Vec2 size = Vec2(10,10));
        ~Map();

        Vec2 map_size;

        void setEntity(std::shared_ptr<Entity> e);
        void clearEntity(Vec2 pos);
        void addItem(Vec2 pos, std::shared_ptr<Item> item);

        Tile* getTile(Vec2 pos);

        void setWall(Vec2 pos);
        void setFloor(Vec2 pos);

        void render(int tile_size, Font font) const;

    protected:
        std::unordered_map<Vec2, Tile, VecHash> tiles;
};

#endif
