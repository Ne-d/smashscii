#pragma once

#include <windows.h>

class Vector2D
{
public:
	// Constructors
	Vector2D() = default;
	Vector2D(float x, float y);
	Vector2D(const Vector2D& other) = default;

	// Vector elements (exceptionally public)
	float x = 0.f;
	float y = 0.f;

	// Utility
	COORD RoundToCoord() const;

	// Operators
	Vector2D& operator=(const Vector2D& vec) = default;
	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator*=(const float& scalar);
	Vector2D& operator/=(const float& scalar);
	
	Vector2D operator+(const Vector2D& vec) const;
	Vector2D operator-(const Vector2D& vec) const;
	Vector2D operator*(const Vector2D& vec) const;
	Vector2D operator/(const Vector2D& vec) const;

	Vector2D operator*(const float& scalar) const;
	Vector2D operator/(const float& scalar) const;
};
