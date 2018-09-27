#include "Projectile.h"



Projectile::Projectile()
{
	rect.setSize(sf::Vector2f(32, 32));
	rect.setFillColor(sf::Color::Green);
	rect.setPosition((800 / 2) - (192 / 2), (600 / 2) - (128 / 2));

	sprite.setPosition((800 / 2) - (192 / 2), (600 / 2) - (128 / 2));
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}


Projectile::~Projectile()
{
}

void Projectile::update() {
	if (direction == 1) { // UP
		rect.move(0, -movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterAnimation * 32, 32 * 3, 32, 32));
	}
	if (direction == 2) {  // DOWN
		rect.move(0, movementSpeed);
		sprite.setTextureRect(sf::IntRect(counterAnimation * 32, 0, 32, 32));
	}
	if (direction == 3) { // LEFT
		rect.move(-movementSpeed, 0);
		sprite.setTextureRect(sf::IntRect(counterAnimation * 32, 32 * 1, 32, 32));
	}
	if (direction == 4) { // RIGHT
		rect.move(movementSpeed, 0);
		sprite.setTextureRect(sf::IntRect(counterAnimation * 32, 32 * 2, 32, 32));
	}

	counterLifeTime++;
	if (counterLifeTime >= lifeTime) {
		destroy = true;
	}

	counterAnimation++;	
	if (counterAnimation >= 2) {
		counterAnimation = 0;
	}

	// SPRITE SET AT RECT
	sprite.setPosition(rect.getPosition());
}
