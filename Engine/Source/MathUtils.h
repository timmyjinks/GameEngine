#pragma once
#include <cmath>

namespace Math {
	constexpr float Pi = 3.14159265359f; // 180
	constexpr float TwoPi = 6.28318530718f; // 360
	constexpr float HalfPi = 1.57079632679f; // 90

	constexpr float RadToDeg(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegToRad(float degrees) { return degrees * (Pi / 180.0f); }


	inline float Sin(float radians) {
		return std::sinf(radians);
	}

	inline float Cos(float radians) {
		return std::cosf(radians);
	}

	inline float ATan2(float y, float x) {
		return std::atan2f(y, x);
	}

	inline float Sqrt(float value) {
		return std::sqrtf(value);
	}

	template<typename T>
	inline T Max(T a, T b) {
		return (a > b) ? a : b;
	}

	template<typename T>
	inline T Min(T a, T b) {
		return (a < b) ? a : b;
	}

	template<typename T>
	inline T Absolute(T value) {
		return (value < 0) ? -value : value;
	}

	template<typename T>
	inline T Clamp(T v, T min, T max) {
		if (v < min) return min;
		if (v > max) return max;

		return v;
	}

	inline int Wrap(int value, int max) {
		return value % max + ((value < 0) ? max : 0);
	}

	inline float Wrap(float value, float max) {
		return std::fmodf(value, max) + ((value < 0) ? max : 0);
	}
}
