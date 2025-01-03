#include "vec2.hpp"

#include <functional>
#include <bits/stdc++.h>

// TODO: Add implicit Vec2 -> Vector2 type conversion

// Equality overload for Vec2
bool Vec2::operator==(const Vec2& other) const {
    return this->x == other.x && this-> y == other.y;
}

// Add hash operator
size_t VecHash::operator()(const Vec2& p) const {
    return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
}

// Allow adding of Vec2s with +=
Vec2& Vec2::operator+=(const Vec2& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

// Allow adding of Vec2s with +
Vec2 operator+(Vec2 lhs, const Vec2& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
}

Vec2 Vec2::randomVec(int min_x, int max_x, int min_y, int max_y) {
    return Vec2(rand() % (max_x + 1 - min_x) + min_x, rand() % (max_y - min_y) + min_y);
}
