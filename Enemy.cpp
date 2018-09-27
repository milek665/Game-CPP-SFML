#include "Enemy.h"



Enemy::Enemy()
{
	rect.setSize(sf::Vector2f(64, 64));
	rect.setFillColor(sf::Color::White);
	rect.setPosition((400 / 2) - (192 / 2), (600 / 2) - (128 / 2));

	sprite.setTextureRect(sf::IntRect(0, 64 * 10, 64, 64));
	sprite.setPosition((800 / 2) - (192 / 2), (600 / 2) - (128 / 2));
}


Enemy::~Enemy()
{
}

void Enemy::update() {
	sprite.setPosition(rect.getPosition());
	text.setPosition(rect.getPosition().x, rect.getPosition().y + 60);
	if (isBlood == true) {
		bloodCounter++;
		if (bloodCounter >= bloodLifeTime) {
			alive = false;
		}
	}
}

void Enemy::updateMovement() {

	if (direction == 1) { // UP
		if (canMoveUp == true) {
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 8, 64, 64));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (direction == 2) { // DOWN
		if (canMoveDown == true) {
			rect.move(0, movementSpeed);
			sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 10, 64, 64));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (direction == 3) { // LEFT
		if (canMoveLeft == true) {
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 9, 64, 64));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (direction == 4) { // RIGHT
		if (canMoveRight == true) {
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 11, 64, 64));
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else {
		// NOTHING MOVEMENT
	}

	counterWalking++;

	if (counterWalking == 8) {
		counterWalking = 0;
	}

	counter++;

	if (counter >= movementLenght) {
		direction = generateRandom(10);
		counter = 0;
	}
}
