#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"

class TextDisplay : public Entity
{
public:
	std::string someString = "Default";
	int movementSpeed = 2;
	int counter = 0;
	int lifeTime = 10;
	bool destroy = false;

	TextDisplay();
	~TextDisplay();
	void update();
};

