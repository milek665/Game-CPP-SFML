#include "Player.h"



Player::Player()
{
	rect.setSize(sf::Vector2f(64, 64));
	rect.setFillColor(sf::Color::White);
	rect.setPosition((1920 / 2) - (192 / 2), (1080 / 2) - (128 / 2));

	sprite.setPosition((1920 / 2) - (192 / 2), (1080 / 2) - (128 / 2));
	sprite.setTextureRect(sf::IntRect(0, 64 * 10, 64, 64));
}


Player::~Player()
{
}

void Player::update() {
	sprite.setPosition(rect.getPosition());
}

void Player::updateMovement() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (canMoveUp == true) {
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 8, 64, 64));
			direction = 1;

			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (canMoveDown == true) {
			rect.move(0, movementSpeed);
			sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 10, 64, 64));
			direction = 2;

			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (canMoveLeft == true) {
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 9, 64, 64));
			direction = 3;

			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (canMoveRight == true) {
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect(counterWalking * 64, 64 * 11, 64, 64));
			direction = 4;

			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		sprite.setTextureRect(sf::IntRect(counterSpelling * 64, 64 * 2, 64, 64));
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		sprite.setTextureRect(sf::IntRect(counterEnjoy * 64, 64 * 20, 64, 64));
	}

	else {
		// NOTHING MOVEMENT
	}

	counterWalking++;

	if (counterWalking == 8) {
		counterWalking = 0;
	}

	counterSpelling++;

	if (counterSpelling == 6) {
		counterSpelling = 0;
	}

	counterEnjoy++;

	if (counterEnjoy == 5) {
		counterEnjoy = 0;
	}
}
