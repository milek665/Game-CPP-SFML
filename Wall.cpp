#include "Wall.h"



Wall::Wall()
{
	rect.setSize(sf::Vector2f(100, 100));
	rect.setFillColor(sf::Color::Cyan);
	rect.setPosition(0, 0);
}


Wall::~Wall()
{
}

void Wall::update() {

}
