#pragma once
#include <windows.h>
#include "Image.h"
#include "Vector2D.h"

class Entity
{
public:
	Entity() = default;
	Entity(COORD& size);
	Entity(COORD& size, Vector2D<float>& spawnPosition);

	Image& GetImage();

	const Vector2D<float>& GetPosition() const;
	void SetPosition(Vector2D<float>& newPosition);
	void Move(Vector2D<float>& direction);

private:
	Image image;
	Vector2D<float> position;
};