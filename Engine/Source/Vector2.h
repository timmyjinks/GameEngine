#pragma once
#include <cmath>

struct Vector2 {
	float x;
	float y;

	Vector2() = default;
	Vector2(float x, float y) { this->x = x; this->y = y; }
	Vector2(int x, int y) { this->x = (float)x; this->y = (float)y; }

	Vector2 Add(Vector2 v) { return Vector2{ x + v.x, y + v.y }; }

	Vector2 operator + (Vector2 v) const { return Vector2{ x + v.x, y + v.y }; }
	Vector2 operator - (Vector2 v) const { return Vector2{ x - v.x, y - v.y }; }
	Vector2 operator * (Vector2 v) const { return Vector2{ x * v.x, y * v.y }; }
	Vector2 operator / (Vector2 v) const { return Vector2{ x / v.x, y / v.y }; }

	Vector2 operator + (float s) const { return Vector2{ x + s , y + s }; }
	Vector2 operator - (float s) const { return Vector2{ x - s , y - s }; }
	Vector2 operator * (float s) const { return Vector2{ x * s , y * s }; }
	Vector2 operator / (float s) const { return Vector2{ x / s , y / s }; }

	float LengthSqr() { return (y * x) + (y * y); }
	float Length() { return std::sqrt((y * x) + (y * y)); }
};
