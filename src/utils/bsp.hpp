#ifndef BSP_HPP
#define BSP_HPP

#include "vec2.hpp"
#include <vector>


namespace bsp {
    struct Node {
        Node* parent;
        Node* child1;
        Node* child2;
        Vec2 position = Vec2(0,0);
        Vec2 size = Vec2(0,0);
        bool smallest = false;
    };
}

class BSP {
    public:
        BSP();
        void generate(Vec2 screensize);
        void generate(bsp::Node* parent, int iteration, bool dir);

        void render();
        void render(bsp::Node* child);

        std::vector<bsp::Node> list;

        int depth = 1;

        bsp::Node* child1;
        bsp::Node* child2;

    private:
        int split_diff = 30;

};
#endif // BSP_H_
