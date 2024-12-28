#ifndef VEC2_HPP
#define VEC2_HPP

#include <cstddef>
#include <raylib.h>

class Vec2 {
    public:

        Vec2();

        static Vec2 randomVec(int min_x, int max_x, int min_y, int max_y);

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
