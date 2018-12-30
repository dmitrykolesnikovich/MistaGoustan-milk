#ifndef _VECTOR2D_
#define _VECTOR2D_

#include <math.h>

struct Vector2d
{
	float x;
	float y;

	Vector2d() 
		: x(0)
		, y(0)
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

	bool operator ==(const Vector2d& v2)
	{
		return x == v2.x && y == v2.y;
	}

	Vector2d operator +(const Vector2d& v2)
	{
		return Vector2d(x + v2.x, y + v2.y);
	}

	Vector2d operator *(float s)
	{
		return Vector2d(x * s, y * s);
	}

	Vector2d operator /(float s)
	{
		return Vector2d(x / s, y / s);
	}

	float magnitude()
	{
		return sqrt(x * x + y * y);
	}

	Vector2d normalize()
	{
		return *this / magnitude();
	}
};

#endif
