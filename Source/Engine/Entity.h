#pragma once
#include <windows.h>
#include "Image.h"
#include "Vector2D.h"

class Entity
{
public:
	// Constructors
	Entity() = delete;
	explicit Entity(COORD size);
	Entity(COORD size, const Vector2D& spawnPosition);
	Entity(const Vector2D& spawnPosition, const std::string& filename, WORD color);

	// Accessors
	virtual const Image& GetImage() const;
	const Vector2D& GetPosition() const;
	void SetPosition(const Vector2D& newPosition);
	void SetPosition(float x, float y);
	
	void Move(const Vector2D& direction);

private: // Data
	Image image;
	Vector2D position;
};