#include "Entity.h"

Entity::Entity(COORD size)
	:
	image(size),
	position()
{
}

Entity::Entity(COORD size, Vector2D spawnPosition)
	:
	image(size),
	position(spawnPosition)
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

void Entity::SetPosition(Vector2D& newPosition)
{
	this->position = position;
}

void Entity::SetPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}

void Entity::Move(Vector2D& direction)
{
	this->position += direction;
}