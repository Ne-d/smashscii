#include "Entity.h"

Entity::Entity(const COORD size)
	:
	image(size)
{
}

Entity::Entity(const COORD size, const Vector2D spawnPosition)
	:
	image(size),
	position(spawnPosition)
{
}

Entity::Entity(const Vector2D spawnPosition, std::string filename, WORD color) : image(filename, color), position(spawnPosition)
{

}

Image& Entity::GetImage()
{
	return this->image;
}

const Vector2D& Entity::GetPosition() const
{
	return this->position;
}

void Entity::SetPosition(const Vector2D newPosition)
{
	this->position = newPosition;
}

void Entity::SetPosition(const float x, const float y)
{
	this->position.x = x;
	this->position.y = y;
}

void Entity::Move(const Vector2D direction)
{
	this->position += direction;
}

void Entity::ReturnToSpawnPosition()
{
	this->position = spawnPosition;
}