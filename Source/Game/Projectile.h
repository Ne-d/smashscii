#pragma once
#include "../Engine/Entity.h"
class Projectile : public Entity
{
public:
	Projectile() = delete;
	explicit Projectile(float x = 0, float y = 0, WORD team = 0, bool isVisible = false);
	~Projectile();

	void Update();

	void Fire(const Vector2D& playerPosition, const Vector2D velocity);

	bool CheckFireState();

private:
	void CheckCollisions();
	void CheckBounds();
	void CheckObjectCollision();

	WORD team;

	Vector2D velocity;

	bool collision = false;
	bool isFired = false;

	const float attackRange = 1.f;
	const int attackDamage = 5;
};

