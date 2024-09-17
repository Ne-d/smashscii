#pragma once
class Vector2D
{
public:

	Vector2D() = default;
	Vector2D(float x, float y);

	float x, y = 0.0f;


	Vector2D& operator=(const Vector2D& vec);

	Vector2D operator+(const Vector2D& vec);
	Vector2D operator-(const Vector2D& vec);
	Vector2D operator*(const Vector2D& vec);
	Vector2D operator/(const Vector2D& vec);
};

