#include "Entity.h"

Entity::Entity(COORD& size)
{
	this->image = Image(size);
	this->position = Vector2D();
}

Entity::Entity(COORD& size, Vector2D& spawnPosition)
{
	this->image = Image(size);
	this->position = spawnPosition;
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

void Entity::Move(Vector2D& direction)
{
	this->position += direction;
}