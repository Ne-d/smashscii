#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

COORD Vector2D::RoundToCoord() const
{
	return COORD{
		static_cast<SHORT>(std::round(x)),
		static_cast<SHORT>(std::round(y))
	};
}

Vector2D& Vector2D::operator=(const Vector2D& vec)
{
	this->x = vec.x;
	this->y = vec.y;

	return *this;
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


Vector2D Vector2D::operator+(const Vector2D& vec)
{
	Vector2D newVec;
	
	newVec.x = this->x + vec.x;
	newVec.y = this->y + vec.y;

	return newVec;
}


Vector2D Vector2D::operator-(const Vector2D& vec)
{
	Vector2D newVec;

	newVec.x = this->x - vec.x;
	newVec.y = this->y - vec.y;

	return newVec;
}


Vector2D Vector2D::operator*(const Vector2D& vec)
{
	Vector2D newVec;

	newVec.x = this->x * vec.x;
	newVec.y = this->y * vec.y;

	return newVec;
}


Vector2D Vector2D::operator/(const Vector2D& vec)
{
	Vector2D newVec;

	newVec.x = this->x / vec.x;
	newVec.y = this->y / vec.y;

	return newVec;
}


