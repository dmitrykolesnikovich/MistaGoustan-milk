#ifndef _VECTOR2D_
#define _VECTOR2D_

#include <math.h>

struct Vector2d
{
	float x;
	float y;

	Vector2d() = default;

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

	Vector2d& operator /=(float scalar) 
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
};

inline bool operator ==(const Vector2d& v, const Vector2d& v2)
{
	return v.x == v2.x && v.y == v2.y;
}

inline Vector2d operator +(const Vector2d& v, const Vector2d& v2)
{
	return Vector2d(v.x + v2.x, v.y + v2.y);
}

inline Vector2d operator *(const Vector2d& v, float s) 
{
	return Vector2d(v.x * s, v.y * s);
}

inline Vector2d operator /(const Vector2d& v, float s)
{
	return Vector2d(v.x / s, v.y / s);
}

inline float magnitude(const Vector2d& v) 
{
	return sqrt(v.x * v.x + v.y * v.y);
}\

inline Vector2d normalize(const Vector2d& v) 
{
	return v / magnitude(v);
}

#endif
