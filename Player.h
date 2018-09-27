#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
public:
	int movementSpeed = 2;
	int attackDamage = 5;
	bool powerUp = false;
	bool novaAttack = false;
	int counterWalking = 0;
	int counterSpelling = 0;
	int counterEnjoy = 0;
	int direction = 0; // 1 - UP, 2 - DOWN, 3 - LEFT, 4 - RIGHT
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	int hp = 100;
	int maxHp = 100;
	int gold = 100;

	Player();
	~Player();

	void update();
	void updateMovement();
protected:

private: 
};

