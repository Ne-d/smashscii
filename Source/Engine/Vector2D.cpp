#include "Vector2D.h"

template <typename T>
Vector2D<T>::Vector2D(T x, T y)
{
	this->x = x;
	this->y = y;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator=(const Vector2D& vec)
{
	this->x = vec.x;
	this->y = vec.y;

	return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator+=(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator-=(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator*=(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator/=(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D& vec)
{
	Vector2D newVec;
	
	newVec.x = this->x + vec.x;
	newVec.y = this->y + vec.y;

	return newVec;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D& vec)
{
	Vector2D newVec;

	newVec.x = this->x - vec.x;
	newVec.y = this->y - vec.y;

	return newVec;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator*(const Vector2D& vec)
{
	Vector2D newVec;

	newVec.x = this->x * vec.x;
	newVec.y = this->y * vec.y;

	return newVec;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator/(const Vector2D& vec)
{
	Vector2D newVec;

	newVec.x = this->x / vec.x;
	newVec.y = this->y / vec.y;

	return newVec;
}


