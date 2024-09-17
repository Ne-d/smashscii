#include "Vector2D.h"

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::operator=(const Vector2D& vec)
{
	this->x = vec.x;
	this->y = vec.y;
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


