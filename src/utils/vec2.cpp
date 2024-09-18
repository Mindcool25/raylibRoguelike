#include "vec2.hpp"
#include "raylib.h"

// Stuff to make the vec2 class hashable
bool Vec2::operator==(const Vec2& other) const {
    return this->x == other.x && this-> y == other.y;
}

size_t VecHash::operator()(const Vec2& p) const {
    return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Vec2 operator+(Vec2 lhs, const Vec2& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
}
