#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"

class Pickup : public Entity
{
public:
	bool isCoin = false;
	bool isPowerUp = false;
	bool isNovaPowerUp = false;	
	bool destroy = false;
	int coinValue = 10;
	bool inShop = false;
	int cost = 10;
	bool isHpShield = false;

	Pickup();
	~Pickup();
	void update();
};

