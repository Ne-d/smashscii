#include "Entity.h"

Entity::Entity(COORD& size)
{
	this->image = Image(size);
	this->position = Vector2D();
}

Entity::Entity(COORD& size, Vector2D spawnPosition)
{
	this->image = Image(size);
	this->position = Vector2D(spawnPosition);
}

const CHAR_INFO** Entity::GetImageTable() const
{
	return this->image.GetTable();
}

const COORD& Entity::GetImageSize() const
{
	return this->image.GetSize();
}

const Vector2D& Entity::GetPosition() const
{
	return this->position;
}