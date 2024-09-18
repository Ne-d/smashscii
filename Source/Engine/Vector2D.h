#pragma once
class Vector2D
{
public:
	Vector2D() = default;
	Vector2D(float x, float y);

	float x = 0.f;
	float y = 0.f;

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

