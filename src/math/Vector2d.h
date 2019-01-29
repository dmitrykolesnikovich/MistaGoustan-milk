#ifndef MILK_VECTOR2D_H
#define MILK_VECTOR2D_H

#include <cmath>

namespace milk
{
    struct Vector2d
    {
        float x;
        float y;

        Vector2d()
                : x(0),
                  y(0)
        {
        }

        Vector2d(float a, float b)
        {
            x = a;
            y = b;
        }

        Vector2d& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;

            return (*this);
        }

        Vector2d& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;

            return (*this);
        }

        Vector2d& operator+=(Vector2d v)
        {
            x += v.x;
            y += v.y;

            return (*this);
        }

        bool operator==(const Vector2d& v2)
        {
            return x == v2.x && y == v2.y;
        }

        Vector2d operator+(const Vector2d& v2)
        {
            return {x + v2.x, y + v2.y};
        }

        Vector2d operator*(float s)
        {
            return {x * s, y * s};
        }

        Vector2d operator/(float s)
        {
            return {x / s, y / s};
        }

        float magnitude()
        {
            return std::sqrt(x * x + y * y);
        }

        Vector2d normalize()
        {
            return *this / magnitude();
        }
    };
}

#endif
