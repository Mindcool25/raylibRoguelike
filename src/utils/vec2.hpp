#ifndef VEC2_HPP
#define VEC2_HPP

#include "raylib.h"
#include <unordered_map>
#include <cstddef>

class Vec2 {
    public:

        Vec2();

        int x, y;

        Vec2(int x, int y) : x(x), y(y) {}

        void vector();

        bool operator==(const Vec2& other) const;
        Vec2& operator+=(const Vec2& rhs);
        friend Vec2 operator+(Vec2 lhs, const Vec2& rhs);
};

struct VecHash {
    std::size_t operator()(const Vec2& p) const;
};

#endif // VEC2_HPP
