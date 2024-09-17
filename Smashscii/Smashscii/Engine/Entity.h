#pragma once
#include <windows.h>
#include "Image.h"
#include "Vector2D.h"

class Entity
{
public:
	Entity() = default;
	Entity(COORD& size);
	Entity(COORD& size, Vector2D spawnPosition);

	const CHAR_INFO** GetImageTable() const;
	const COORD& GetImageSize() const;
	const Vector2D& GetPosition() const;

private:
	Image image;
	Vector2D position;
};

