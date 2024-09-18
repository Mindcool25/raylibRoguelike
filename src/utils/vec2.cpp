#include "vec2.hpp"

// Stuff to make the vec2 class hashable
bool Vec2::operator==(const Vec2& other) const {
    return this->x == other.x && this-> y == other.y;
}

size_t VecHash::operator()(const Vec2& p) const {
    return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
}

Vector2 Vec2::vector() {
    return Vector2(this->x, this->y);
}

Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
}
