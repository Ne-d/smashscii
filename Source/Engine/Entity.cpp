#include "Entity.h"

Entity::Entity(COORD& size)
{
	this->image = Image(size);
	this->position = Vector2D<float>();
}

Entity::Entity(COORD& size, Vector2D<float>& spawnPosition)
{
	this->image = Image(size);
	this->position = spawnPosition;
}

Image& Entity::GetImage()
{
	return this->image;
}

const Vector2D<float>& Entity::GetPosition() const
{
	return this->position;
}

void Entity::SetPosition(Vector2D<float>& newPosition)
{
	this->position = position;
}

void Entity::Move(Vector2D<float>& direction)
{
	this->position += direction;
}