#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"

class Projectile : public Entity
{
public:
	int movementSpeed = 20;
	int attackDamage = 5;
	int direction = 0; // 1 - UP, 2 - DOWN, 3 - LEFT, 4 - RIGHT
	bool destroy = false;
	int counterLifeTime = 0;
	int lifeTime = 30;
	int counterAnimation = 0;

	Projectile();
	~Projectile();
	void update();
};

