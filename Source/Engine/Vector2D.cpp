#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D(const float x, const float y)
	:
	x(x),
	y(y)
{
}

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
