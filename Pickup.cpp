#include "Pickup.h"



Pickup::Pickup()
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Yellow);
}


Pickup::~Pickup()
{
}

void Pickup::update() {
	sprite.setPosition(rect.getPosition());
	text.setPosition(rect.getPosition().x - 20, rect.getPosition().y - 30);
}