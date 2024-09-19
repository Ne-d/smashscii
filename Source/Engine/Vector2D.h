#pragma once
#include <Windows.h>

class Vector2D
{
public:
	Vector2D() = default;
	Vector2D(float x, float y);

	float x = 0.f;
	float y = 0.f;

public:
	COORD RoundToCoord() const;

	Vector2D& operator=(const Vector2D& vec);
	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D operator+(const Vector2D& vec);
	Vector2D operator-(const Vector2D& vec);
	Vector2D operator*(const Vector2D& vec);
	Vector2D operator/(const Vector2D& vec);
};

