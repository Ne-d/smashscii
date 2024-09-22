#pragma once
#include <windows.h>
#include "Image.h"
#include "Vector2D.h"

class Entity
{
public:
	Entity() = delete;
	Entity(COORD size);
	Entity(COORD size, Vector2D spawnPosition);
	Entity(Vector2D spawnPosition, std::string filename, WORD color);

	Image& GetImage();

	const Vector2D& GetPosition() const; // TODO: Check this doesn't return a reference to a local variable
	void SetPosition(const Vector2D newPosition);
	void SetPosition(float x, float y);
	void Move(const Vector2D direction);
	void ReturnToSpawnPosition();

private:
	Image image;
	Vector2D position;
	Vector2D spawnPosition;
};