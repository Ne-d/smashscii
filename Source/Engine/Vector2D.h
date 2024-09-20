#pragma once

#include <windows.h>

class Vector2D
{
public:
	Vector2D() = default;
	Vector2D(float x, float y);

	float x = 0.f;
	float y = 0.f;
	
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
