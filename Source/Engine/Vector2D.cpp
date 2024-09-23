#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D(const float x, const float y)
	:
	x(x),
	y(y)
{
}

/**
 * Converts a Vector2D to a COORD, rounding the values.
 * @return A COORD containing the rounded values of the Vector2D.
 */
COORD Vector2D::RoundToCoord() const
{
	return COORD{
		static_cast<SHORT>(std::round(x)),
		static_cast<SHORT>(std::round(y))
	};
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

// Dot product between two vectors.
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D& Vector2D::operator*=(const float& scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

Vector2D& Vector2D::operator/=(const float& scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	return *this;
}

// Dot product between two vectors.
Vector2D Vector2D::operator+(const Vector2D& vec) const
{
	Vector2D newVec(*this);
	newVec += vec;
	return newVec;
}


Vector2D Vector2D::operator-(const Vector2D& vec) const
{
	Vector2D newVec(*this);
	newVec -= vec;
	return newVec;
}


Vector2D Vector2D::operator*(const Vector2D& vec) const
{
	Vector2D newVec(*this);
	newVec *= vec;
	return newVec;
}


Vector2D Vector2D::operator/(const Vector2D& vec) const
{
	Vector2D newVec(*this);
	newVec /= vec;
	return newVec;
}

Vector2D Vector2D::operator*(const float& scalar) const
{
	Vector2D newVec(*this);
	newVec *= scalar;
	return newVec;
}

Vector2D Vector2D::operator/(const float& scalar) const
{
	Vector2D newVec(*this);
	newVec /= scalar;
	return newVec;
}
