#pragma once
#include <windows.h>
#include "Image.h"
#include "Vector2D.h"

class Entity
{
public:
	Entity() = default;
	Entity(COORD& size);
	Entity(COORD& size, Vector2D& spawnPosition);

	Image& GetImage();

	const Vector2D& GetPosition() const;
	void SetPosition(Vector2D& newPosition);
	void SetPosition(float x, float y);
	void Move(Vector2D& direction);

private:
	Image image;
	Vector2D position;
};