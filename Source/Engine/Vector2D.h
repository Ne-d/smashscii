#pragma once
template <typename T>
class Vector2D
{
public:

	Vector2D() = default;
	Vector2D(T x, T y);

	T x, y = 0;


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

