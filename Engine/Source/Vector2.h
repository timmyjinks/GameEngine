#pragma once
#include "MathUtils.h"
#include <cmath>

struct Vector2 {
	float x;
	float y;

	Vector2() = default;
	Vector2(float x, float y) { this->x = x; this->y = y; }
	Vector2(int x, int y) { this->x = (float)x; this->y = (float)y; }

	float operator[] (unsigned int index) const { return (&x)[index]; }
	float& operator[] (unsigned int index) { return (&x)[index]; }

	Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
	Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
	Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
	Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

	Vector2 operator + (float s) const { return Vector2{ x + s , y + s }; }
	Vector2 operator - (float s) const { return Vector2{ x - s , y - s }; }
	Vector2 operator * (float s) const { return Vector2{ x * s , y * s }; }
	Vector2 operator / (float s) const { return Vector2{ x / s , y / s }; }

	Vector2& operator += (Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2& operator -= (Vector2& v) { x -= v.x; y -= v.y; return *this; }
	Vector2& operator *= (Vector2& v) { x *= v.x; y *= v.y; return *this; }
	Vector2& operator /= (Vector2& v) { x /= v.x; y /= v.y; return *this; }

	Vector2& operator += (float s) { x += s; y += s; return *this; }
	Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
	Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
	Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

	float LengthSqr() { return (y * x) + (y * y); }
	float Length() { return Math::Sqrt((y * x) + (y * y)); }

	float Angle() { return Math::ATan2(y, x); }

	Vector2 Rotate(float radians) const;
};

inline Vector2 Vector2::Rotate(float radians) const {
	float x_ = x * Math::Cos(radians) - y * Math::Sin(radians);
	float y_ = x * Math::Sin(radians) + y * Math::Cos(radians);

	return { x_, y_ };
}
