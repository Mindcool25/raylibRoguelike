#include "bsp.hpp"
#include "raylib.h"
#include "vec2.hpp"
#include <iostream>

BSP::BSP() {
    this->child1 = nullptr;
    this->child2 = nullptr;
}

void BSP::generate(Vec2 screensize) {
    // Create children
    bsp::Node node1;
    bsp::Node node2;
    this->child1 = &node1;
    this->child2 = &node2;

    // Set children size and origin
    int split = screensize.x / 2;

    node1.position = Vec2(0, 0);
    node1.size = Vec2(split, screensize.y);

    node2.position = Vec2(split, 0);
    node2.size = Vec2(screensize.x - split, screensize.y);

    this->generate(this->child1, depth, true);
    this->generate(this->child2, depth, true);
}

void BSP::generate(bsp::Node* parent, int iteration, bool dir) {
    std::cout << "COORDS: " << parent->position.x << "," << parent->position.y << std::endl;
    std::cout << "SIZE: " << parent->size.x << "," << parent->size.y << std::endl;
    if (iteration == 0) {
        std::cout << "at the end" << std::endl;
        return;
    } else {
        bsp::Node* n1 = new bsp::Node();
        bsp::Node* n2 = new bsp::Node();
        if (dir) {
            int split = parent->size.y / 2;
            Vec2 n1_pos = parent->position;
            Vec2 n2_pos = Vec2(parent->position.x, parent->position.y + split);
            Vec2 n1_size = Vec2(parent->size.x, split);
            Vec2 n2_size = Vec2(parent->size.x, parent->size.y - split);

            n1->size = n1_size;
            n2->size = n2_size;

            n1->position = n1_pos;
            n2->position = n2_pos;
        } else {
            int split = parent->size.x / 2;
            Vec2 n1_pos = parent->position;
            Vec2 n2_pos = Vec2(parent->position.x + split, parent->position.y);
            Vec2 n1_size = Vec2(split, parent->size.y);
            Vec2 n2_size = Vec2(parent->position.x - split, parent->size.y);
            n1->size = n1_size;
            n2->size = n2_size;
            n1->position = n1_pos;
            n2->position = n2_pos;
        }
        this->generate(n1, iteration - 1, !dir);
        this->generate(n2, iteration - 1, !dir);
    }
}


void BSP::render() {
    if (this->child1 == nullptr || this->child2 == nullptr) {
        ClearBackground(WHITE);
    } else {
        this->render(this->child1);
        this->render(this->child2);
    }
}

void BSP::render(bsp::Node* child) {
    std::cout << "COORDS: " << child->position.x << "," << child->position.y << std::endl;
    std::cout << "SIZE: " << child->size.x << "," << child->size.y << std::endl;
    if (child->smallest) {
        DrawRectangleV(child->position.vector(), child->size.vector(), ColorFromHSV(GetRandomValue(100, 355), 64, 100));
    } else {
        DrawRectangleV(child->position.vector(), child->size.vector(), ColorFromHSV(GetRandomValue(100, 355), 64, 100));
        this->render(child->child1);
        this->render(child->child2);
    }
}
