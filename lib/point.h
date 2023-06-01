#pragma once
#include <cmath>
#include "misc/constants.h"

struct point {
	float x, y, z;
	constexpr point(const float x = 0.f, const float y = 0.f, const float z = 0.f) noexcept : x(x), y(y), z(z) {}
	
	// operators
	constexpr const point& operator + (const point& p) const noexcept {
		return point{x+p.x,y+p.y,z+p.z};
	}
	constexpr const point& operator - (const point& p) const noexcept {
		return point{x-p.x,y-p.y,z-p.z};
	}
	constexpr const point& operator * (const float t) const noexcept {
		return point{x*t,y*t,z*t};
	}
	constexpr const point& operator / (const float t) const noexcept {
		return point{x/t,y/t,z/t};
	}

	// aimbot fucks
	constexpr const point& angle() const noexcept { //! (0,0,0) point reference
		return point{ std::atan2(-z, std::hypot(x, y)) * (180.0f / constants::pi<float>),
									std::atan2(y, x) * (180.0f / constants::pi<float>),
									0.0f };
	}

	constexpr point anglediff(const point& target, const point& viewangle) noexcept {
		return (target - *this).angle() - viewangle;
	}
};

inline constexpr const point point000() {
	return point{ 0.0f, 0.0f, 0.0f };
}