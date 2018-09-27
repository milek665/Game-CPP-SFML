#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"

class Wall : public Entity
{
public:
	bool destructable = false;
	int hp = 25;
	bool destroy = false;

	Wall();
	~Wall();
	void update();
};

