#include "Projectile.h"
#include "../Engine/Engine.h"

Projectile::Projectile(float x, float y, WORD team, bool isVisible) :
	Entity(Vector2D(x, y), "./Textures/Projectile.txt", team),
	team(team)
{
	if (isVisible)
		GetImage().Show();
	else
		GetImage().Hide();

	SetPosition(Vector2D(x, y));
}

Projectile::~Projectile()
{

}

void Projectile::Update()
{
	if (!collision && isFired)
	{
		Move(this->velocity);
		CheckCollisions();
	}
}

void Projectile::CheckCollisions()
{
	CheckBounds();
	CheckObjectCollision();
	if (collision = true)
	{
		ReturnToSpawnPosition();
		GetImage().Hide();
		isFired = false;
		collision = false;
	}
}

void Projectile::CheckBounds()
{
	const COORD screenSize = Engine::GetInstance().GetScreenSize();

	if (GetPosition().x + GetImage().GetSize().X >= screenSize.X && velocity.x > 0)
	{
		collision = true;
	}

	if (GetPosition().x <= 0 && velocity.x < 0)
	{
		collision = true;
	}

	if (GetPosition().y + GetImage().GetSize().Y >= screenSize.Y && velocity.y > 0)
	{
		collision = true;
	}

	if (GetPosition().y <= 0 && velocity.y < 0)
	{
		collision = true;
	}
}

void Projectile::CheckObjectCollision()
{

}

void Projectile::Fire(const Vector2D& playerPosition, const Vector2D  velocity)
{
	SetPosition(playerPosition);
	GetImage().Show();
	this->velocity = velocity;
	isFired = true;
}

bool Projectile::CheckFireState()
{
	return this->isFired;
}