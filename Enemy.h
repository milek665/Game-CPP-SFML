#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "Random.h"

class Enemy : public Entity
{
public:
	int movementSpeed = 1;
	int movementLenght = 100;
	int attackDamage = 10;
	int counterWalking = 0;
	int direction = 0;
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	int counter = 0;
	int hp = 50;
	int maxHp = 50;
	bool alive = true;
	bool isBlood = false;
	int bloodCounter = 0;
	int bloodLifeTime = 500;

	Enemy();
	~Enemy();
	void update();
	void updateMovement();
};

