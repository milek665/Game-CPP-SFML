// STANDARD LIBRARY
#include <stdlib.h>
#include <time.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>

// SFML LIBRARY
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>

// GAME FILES
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Random.h"
#include "TextDisplay.h"
#include "Pickup.h"
#include "Wall.h"

// TIME
sf::Clock clock1;
sf::Clock clock2;
sf::Clock clock3;

// ADDITIONAL VARIABLES
float movementSpeed = 2;
int counterWalking = 0;
int counter = 0;
int counter2 = 0;
int counter3 = 0;

int main() {
	srand((unsigned)time(NULL));

	// WINDOW
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "App", sf::Style::Close);
	window.setPosition(sf::Vector2i(((1920 / 2) - (window.getSize().x / 2)), ((1080 / 2) - (window.getSize().y / 2))));
	window.setFramerateLimit(60);

	// VIEW 
	sf::View view1(sf::FloatRect(200, 200, 300, 200));
	view1.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	view1.setCenter(sf::Vector2f(view1.getSize().x / 2, view1.getSize().y / 2));
	window.setView(view1);

	// ICON
	sf::Image icon;
	if (!icon.loadFromFile("Img/Favicon.jpg")) {
		return EXIT_FAILURE;
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// THEME MUSIC
	sf::Music music;
	if (!music.openFromFile("Music/Theme.ogg")) {
		return EXIT_FAILURE;
	}
	music.play();
	music.setLoop(true);

	// SOUND BUFFER DAMAGE
	sf::SoundBuffer bufferDamage;
	if (!bufferDamage.loadFromFile("Music/Damage.wav")) {
		return EXIT_FAILURE;
	}

	// SOUND DAMAGE
	sf::Sound soundDamage;
	soundDamage.setBuffer(bufferDamage);

	// SOUND BUFFER SHOOT
	sf::SoundBuffer bufferShoot;
	if (!bufferShoot.loadFromFile("Music/Shoot.wav")) {
		return EXIT_FAILURE;
	}

	// SOUND SHOOT
	sf::Sound soundShoot;
	soundShoot.setBuffer(bufferShoot);

	// SOUND BUFFER COLLISION 
	sf::SoundBuffer bufferCollision;
	if (!bufferCollision.loadFromFile("Music/Collision.wav")) {
		return EXIT_FAILURE;
	}

	// SOUND COLLISION
	sf::Sound soundCollision;
	soundCollision.setBuffer(bufferCollision);

	// SOUND BUFFER TARGET
	sf::SoundBuffer bufferTarget;
	if (!bufferTarget.loadFromFile("Music/Target.wav")) {
		return EXIT_FAILURE;
	}

	// SOUND TARGET
	sf::Sound soundTarget;
	soundTarget.setBuffer(bufferTarget);

	// SOUND BUFFER DROP COIN
	sf::SoundBuffer bufferDropCoin;
	if (!bufferDropCoin.loadFromFile("Music/DropCoin.wav")) {
		return EXIT_FAILURE;
	}

	// SOUND DROP COIN
	sf::Sound soundDropCoin;
	soundDropCoin.setBuffer(bufferDropCoin);

	// SOUND BUFFER POWER UP
	sf::SoundBuffer bufferPowerUp;
	if (!bufferPowerUp.loadFromFile("Music/PowerUp.wav")) {
		return EXIT_FAILURE;
	}

	// SOUND POWER UP
	sf::Sound soundPowerUp;
	soundPowerUp.setBuffer(bufferPowerUp);

	// SOUND BUFFER NOVA
	sf::SoundBuffer bufferNova;
	if (!bufferNova.loadFromFile("Music/Nova.wav")) {
		return EXIT_FAILURE;
	}

	// SOUND NOVA
	sf::Sound soundNova;
	soundNova.setBuffer(bufferNova);

	// SOUND BUFFER OPENING CHEST
	sf::SoundBuffer bufferOpeningChest;
	if (!bufferOpeningChest.loadFromFile("Music/OpeningChest.wav")) {
		return EXIT_FAILURE;
	}

	// SOUND OPENING CHEST
	sf::Sound soundOpeningChest;
	soundOpeningChest.setBuffer(bufferOpeningChest);

	// TEXTURE PLAYER
	sf::Texture texturePlayer;
	if (!texturePlayer.loadFromFile("Img/Golden-orc.png")) {
		return EXIT_FAILURE;
	}

	// TEXTURE ENEMY
	sf::Texture textureEnemy;
	if (!textureEnemy.loadFromFile("Img/Archer.png")) {
		return EXIT_FAILURE;
	}

	// TEXTURE COIN
	sf::Texture textureCoin;
	if (!textureCoin.loadFromFile("Img/GoldCoinSprite/Coin1.png")) {
		return EXIT_FAILURE;
	}

	// TEXTURE FIREBALL
	sf::Texture textureFireball;
	if (!textureFireball.loadFromFile("Img/FireBall.png")) {
		return EXIT_FAILURE;
	}

	// TEXTURE AROUND POWER UP
	sf::Texture textureAroundPowerUp;
	if (!textureAroundPowerUp.loadFromFile("Img/PowerUps/icon_97.png")) {
		return EXIT_FAILURE;
	}

	// TEXTURE IMPROVED POWER UP
	sf::Texture textureImprovedPowerUp;
	if (!textureImprovedPowerUp.loadFromFile("Img/PowerUps/icon_79.png")) {
		return EXIT_FAILURE;
	}

	// TEXTURE HP SHIELD
	sf::Texture textureHpShield;
	if (!textureHpShield.loadFromFile("Img/PowerUps/icon_12.png")) {
		return EXIT_FAILURE;
	}

	// TEXTURE BLOOD
	sf::Texture textureBlood;
	if (!textureBlood.loadFromFile("Img/Blood.gif")) {
		return EXIT_FAILURE;
	}

	// TEXTURE CRATE
	sf::Texture textureCrate;
	if (!textureCrate.loadFromFile("Img/Crate.png")) {
		return EXIT_FAILURE;
	}

	//TEXTURE WALL
	sf::Texture textureWall;
	if (!textureWall.loadFromFile("Img/Wall.png")) {
		return EXIT_FAILURE;
	}

	// FONT
	sf::Font font;
	if (!font.loadFromFile("Font/Eater-Regular.ttf")) {
		return EXIT_FAILURE;
	}

	// GOLD DISPLAY
	sf::Text text("Gold: ", font, 25);
	text.setFillColor(sf::Color::Yellow);
	text.setPosition(0, 0);
	text.setCharacterSize(25);

	// PLAYER HP DISPLAY
	sf::Text textHp("Hp: ", font, 25);
	textHp.setFillColor(sf::Color::Green);
	textHp.setPosition(0, 0);

	// PLAYER OBJECT
	Player player1;
	player1.sprite.setTexture(texturePlayer);

	// PROJECTILE VECTOR
	std::vector<Projectile>::const_iterator iteratorP;
	std::vector<Projectile> projectileArray;

	// PROJECTILE OBJECT
	Projectile projectile1;
	projectile1.sprite.setTexture(textureFireball);

	// ENEMY VECTOR
	std::vector<Enemy>::const_iterator iteratorE;
	std::vector<Enemy> enemyArray;

	// ENEMY OBJECT
	Enemy enemy1;
	enemy1.sprite.setTexture(textureEnemy);
	enemy1.text.setFont(font);
	enemy1.text.setCharacterSize(17);
	enemy1.text.setFillColor(sf::Color::Red);

	// BLOOD VECTOR
	std::vector<Enemy>::const_iterator iteratorB;
	std::vector<Enemy> bloodArray;

	// BLOOD OBJECT
	Enemy blood1;
	blood1.isBlood = true;
	blood1.sprite.setTexture(textureBlood);
	blood1.sprite.setTextureRect(sf::IntRect(32 * 3, 0, 32, 32));
	blood1.rect.setPosition(600, 200);
	bloodArray.push_back(blood1);

	// TEXT VECTOR
	std::vector<TextDisplay>::const_iterator iteratorT;
	std::vector<TextDisplay> textArray;

	// TEXT OBJECT
	TextDisplay textDisplay1;
	textDisplay1.text.setFont(font);
	textArray.push_back(textDisplay1);

	// PICKUP VECTOR
	std::vector<Pickup>::const_iterator iteratorC;
	std::vector<Pickup> pickupArray;

	// PICKUP OBJECT
	Pickup pickup1;
	pickup1.text.setFont(font);
	pickup1.sprite.setTexture(textureCoin);
	pickup1.rect.setPosition(400, 400);
	//pickupArray.push_back(pickup1);

	// WALL VECTOR
	std::vector<Wall>::const_iterator iteratorW;
	std::vector<Wall> wallArray;

	// WALL OBJECT
	Wall wall1;
	wall1.rect.setPosition(100, 100);
	wall1.sprite.setScale(0.25, 0.25);

	int roomSize = generateRandom(10) + 3;
	int verticalDoorLocationRight = 0;
	int verticalDoorLocationLeft = 0;
	int horizontalDoorLocationUp = 0;
	int horizontalDoorLocationDown = 0;
	int roomStartX = 0;
	int roomStartY = 0;

	// FIRST ROOM
	roomSize = 5;
	verticalDoorLocationRight = 3;
	verticalDoorLocationLeft = 100;
	horizontalDoorLocationUp = 2;
	horizontalDoorLocationDown = 2;
	roomStartX = 0;
	roomStartY = 0;
	wall1.sprite.setTexture(textureWall);
	wall1.destructable = false;

	// CREATE HORIZONTAL WALL
	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != horizontalDoorLocationUp) {
			wall1.rect.setPosition(100 * counter + roomStartX, roomStartY);
			wall1.sprite.setPosition(100 * counter + roomStartX, roomStartY);
			wallArray.push_back(wall1);
		}

		counter++;
	}

	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != horizontalDoorLocationDown) {
			wall1.rect.setPosition(100 * counter + roomStartX, 100 * roomSize + roomStartY);
			wall1.sprite.setPosition(100 * counter + roomStartX, 100 * roomSize + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	// CREATE VERTICAL WALL
	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != verticalDoorLocationLeft) {
			wall1.rect.setPosition(0 + roomStartX, 100 * counter + roomStartY);
			wall1.sprite.setPosition(0 + roomStartX, 100 * counter + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != verticalDoorLocationRight) {
			wall1.rect.setPosition(100 * roomSize + roomStartX, 100 * counter + roomStartY);
			wall1.sprite.setPosition(100 * roomSize + roomStartX, 100 * counter + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	// RANDOM STUFF IN ROOM
	wall1.sprite.setTexture(textureCrate);

	counter = 0;
	while (counter <= roomSize + 1) {
		counter2 = 0;
		while (counter2 <= roomSize + 1) {
			int tempRandom = generateRandom(20);
			if (tempRandom == 1) {
				wall1.destructable = true;
				wall1.rect.setFillColor(sf::Color::Yellow);
				wall1.rect.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				wall1.sprite.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				wallArray.push_back(wall1);
				wall1.destructable = false;
				wall1.rect.setFillColor(sf::Color::Cyan);
			}
			if (tempRandom == 2) {
				enemy1.rect.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				enemyArray.push_back(enemy1);
			}
			counter2++;
		}
		counter++;
	}

	// SECOND ROOM
	roomSize = 10;
	verticalDoorLocationRight = 3;
	verticalDoorLocationLeft = 3;
	horizontalDoorLocationUp = 5;
	horizontalDoorLocationDown = 5;
	roomStartX = 5 * 100;
	roomStartY = 0;
	wall1.destructable = false;
	wall1.sprite.setTexture(textureWall);

	// CREATE HORIZONTAL WALL
	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != horizontalDoorLocationUp) {
			wall1.rect.setPosition(100 * counter + roomStartX, roomStartY);
			wall1.sprite.setPosition(100 * counter + roomStartX, roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != horizontalDoorLocationDown) {
			wall1.rect.setPosition(100 * counter + roomStartX, 100 * roomSize + roomStartY);
			wall1.sprite.setPosition(100 * counter + roomStartX, 100 * roomSize + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	// CREATE VERTICAL WALL
	counter = 0;
	while (counter < roomSize + 1) {
		if(counter != verticalDoorLocationLeft) {
			wall1.rect.setPosition(0 + roomStartX, 100 * counter + roomStartY);
			wall1.sprite.setPosition(0 + roomStartX, 100 * counter + roomStartY);
			wallArray.push_back(wall1);
		}	
		counter++;
	}

	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != verticalDoorLocationRight) {
			wall1.rect.setPosition(100 * roomSize + roomStartX, 100 * counter + roomStartY);
			wall1.sprite.setPosition(100 * roomSize + roomStartX, 100 * counter + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	// RANDOM STUFF IN ROOM
	wall1.sprite.setTexture(textureCrate);
	counter = 0;
	while (counter <= roomSize + 1) {
		counter2 = 0;
		while (counter2 <= roomSize + 1) {
			int tempRandom = generateRandom(20);
			if (tempRandom == 1) {
				wall1.destructable = true;
				wall1.rect.setFillColor(sf::Color::Yellow);
				wall1.rect.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				wall1.sprite.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				wallArray.push_back(wall1);
				wall1.destructable = false;
				wall1.rect.setFillColor(sf::Color::Cyan);
			}
			if (tempRandom == 2) {
				enemy1.rect.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				enemyArray.push_back(enemy1);
			}
			counter2++;
		}
		counter++;
	}

	// THIRD ROOM
	roomSize = 6;
	verticalDoorLocationRight = 3;
	verticalDoorLocationLeft = 3;
	horizontalDoorLocationUp = 5;
	horizontalDoorLocationDown = 5;
	roomStartX = 5 * 100;
	roomStartY = 10 * 100;
	wall1.destructable = false;
	wall1.sprite.setTexture(textureWall);

	// CREATE HORIZONTAL WALL
	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != horizontalDoorLocationUp) {
			wall1.rect.setPosition(100 * counter + roomStartX, roomStartY);
			wall1.sprite.setPosition(100 * counter + roomStartX, roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != horizontalDoorLocationDown) {
			wall1.rect.setPosition(100 * counter + roomStartX, 100 * roomSize + roomStartY);
			wall1.sprite.setPosition(100 * counter + roomStartX, 100 * roomSize + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	// CREATE VERTICAL WALL
	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != verticalDoorLocationLeft) {
			wall1.rect.setPosition(0 + roomStartX, 100 * counter + roomStartY);
			wall1.sprite.setPosition(0 + roomStartX, 100 * counter + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != verticalDoorLocationRight) {
			wall1.rect.setPosition(100 * roomSize + roomStartX, 100 * counter + roomStartY);
			wall1.sprite.setPosition(100 * roomSize + roomStartX, 100 * counter + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	// RANDOM STUFF IN ROOM
	wall1.sprite.setTexture(textureCrate);
	counter = 0;
	while (counter <= roomSize + 1) {
		counter2 = 0;
		while (counter2 <= roomSize + 1) {
			int tempRandom = generateRandom(20);
			if (tempRandom == 1) {
				wall1.destructable = true;
				wall1.rect.setFillColor(sf::Color::Yellow);
				wall1.rect.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				wall1.sprite.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				wallArray.push_back(wall1);
				wall1.destructable = false;
				wall1.rect.setFillColor(sf::Color::Cyan);
			}
			if (tempRandom == 2) {
				enemy1.rect.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				enemyArray.push_back(enemy1);
			}
			counter2++;
		}
		counter++;
	}

	// FORTH ROOM
	roomSize = 10;
	verticalDoorLocationRight = 100;
	verticalDoorLocationLeft = 100;
	horizontalDoorLocationUp = 100;
	horizontalDoorLocationDown = 5;
	roomStartX = 5 * 100;
	roomStartY = -1 * (10 * 100);
	wall1.destructable = false;
	wall1.sprite.setTexture(textureWall);

	// CREATE HORIZONTAL WALL
	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != horizontalDoorLocationUp) {
			wall1.rect.setPosition(100 * counter + roomStartX, roomStartY);
			wall1.sprite.setPosition(100 * counter + roomStartX, roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != horizontalDoorLocationDown) {
			wall1.rect.setPosition(100 * counter + roomStartX, 100 * roomSize + roomStartY);
			wall1.sprite.setPosition(100 * counter + roomStartX, 100 * roomSize + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	// CREATE VERTICAL WALL
	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != verticalDoorLocationLeft) {
			wall1.rect.setPosition(0 + roomStartX, 100 * counter + roomStartY);
			wall1.sprite.setPosition(0 + roomStartX, 100 * counter + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != verticalDoorLocationRight) {
			wall1.rect.setPosition(100 * roomSize + roomStartX, 100 * counter + roomStartY);
			wall1.sprite.setPosition(100 * roomSize + roomStartX, 100 * counter + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	// RANDOM STUFF IN ROOM
	wall1.sprite.setTexture(textureCrate);
	counter = 0;
	while (counter <= roomSize + 1) {
		counter2 = 0;
		while (counter2 <= roomSize + 1) {
			int tempRandom = generateRandom(20);
			if (tempRandom == 1) {
				wall1.destructable = true;
				wall1.rect.setFillColor(sf::Color::Yellow);
				wall1.rect.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				wall1.sprite.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				wallArray.push_back(wall1);
				wall1.destructable = false;
				wall1.rect.setFillColor(sf::Color::Cyan);
			}
			if (tempRandom == 2) {
				enemy1.rect.setPosition((counter * 100) + 100 + roomStartX, (counter2 * 100) + 100 + roomStartY);
				enemyArray.push_back(enemy1);
			}
			counter2++;
		}
		counter++;
	}

	// ITEM SHOP
	roomSize = 8;
	verticalDoorLocationRight = 100;
	verticalDoorLocationLeft = 3;
	horizontalDoorLocationUp = 100;
	horizontalDoorLocationDown = 100;
	roomStartX = 15 * 100;
	roomStartY = 0;
	wall1.destructable = false;
	wall1.sprite.setTexture(textureWall);

	// CREATE HORIZONTAL WALL
	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != horizontalDoorLocationUp) {
			wall1.rect.setPosition(100 * counter + roomStartX, roomStartY);
			wall1.sprite.setPosition(100 * counter + roomStartX, roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != horizontalDoorLocationDown) {
			wall1.rect.setPosition(100 * counter + roomStartX, 100 * roomSize + roomStartY);
			wall1.sprite.setPosition(100 * counter + roomStartX, 100 * roomSize + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	// CREATE VERTICAL WALL
	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != verticalDoorLocationLeft) {
			wall1.rect.setPosition(0 + roomStartX, 100 * counter + roomStartY);
			wall1.sprite.setPosition(0 + roomStartX, 100 * counter + roomStartY);
			wallArray.push_back(wall1);
		}
		counter++;
	}

	counter = 0;
	while (counter < roomSize + 1) {
		if (counter != verticalDoorLocationRight) {
			wall1.rect.setPosition(100 * roomSize + roomStartX, 100 * counter + roomStartY);
			wall1.sprite.setPosition(100 * roomSize + roomStartX, 100 * counter + roomStartY);
			wallArray.push_back(wall1);
		}

		counter++;
	}

	// POWER UP
	pickup1.cost = 15;
	pickup1.text.setString("Cost:" + std::to_string(pickup1.cost));
	pickup1.text.setCharacterSize(20);
	pickup1.inShop = true;
	pickup1.isCoin = false;
	pickup1.isPowerUp = true;
	pickup1.isNovaPowerUp = false;
	pickup1.sprite.setTexture(textureImprovedPowerUp);
	pickup1.rect.setPosition((15 * 100) + (3 * 100), (4 * 100));
	pickupArray.push_back(pickup1);

	// NOVA
	pickup1.cost = 30;
	pickup1.text.setString("Cost: " + std::to_string(pickup1.cost));
	pickup1.text.setCharacterSize(20);
	pickup1.cost = 30;
	pickup1.inShop = true;
	pickup1.isCoin = false;
	pickup1.isPowerUp = false;
	pickup1.isNovaPowerUp = true;
	pickup1.sprite.setTexture(textureAroundPowerUp);
	pickup1.rect.setPosition((15 * 100) + (4 * 100), (4 * 100));
	pickupArray.push_back(pickup1);
	pickup1.inShop = false;

	// HP SHIELD
	pickup1.cost = 100;
	pickup1.text.setString("Cost: " + std::to_string(pickup1.cost));
	pickup1.text.setCharacterSize(20);
	pickup1.cost = 30;
	pickup1.inShop = true;
	pickup1.isCoin = false;
	pickup1.isPowerUp = false;
	pickup1.isNovaPowerUp = false;
	pickup1.isHpShield = true;
	pickup1.sprite.setTexture(textureHpShield);
	pickup1.rect.setPosition((15 * 100) + (5 * 100), (4 * 100));
	pickupArray.push_back(pickup1);
	pickup1.inShop = false;
	pickup1.isHpShield = false;

		// LOOP OF PROGRAM
		while (window.isOpen()) {
			sf::Event e;

			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed) {
					window.close();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();
				}
			}

			// CLEAR WINDOW
			window.clear(sf::Color(50, 111, 171));

			// CLOCK
			sf::Time elapsed1 = clock1.getElapsedTime();
			sf::Time elapsed2 = clock2.getElapsedTime();
			sf::Time elapsed3 = clock3.getElapsedTime();

			// PROJECTILE COLLIDES WITH WALL
			counter = 0;
			for (iteratorP = projectileArray.begin(); iteratorP != projectileArray.end(); iteratorP++) {
				counter2 = 0;
					for (iteratorW = wallArray.begin(); iteratorW != wallArray.end(); iteratorW++) {
						if (projectileArray[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds())) {
							soundTarget.play();
							projectileArray[counter].destroy = true;
							if (wallArray[counter2].destructable == true) {
								wallArray[counter2].hp -= player1.attackDamage;
								if (wallArray[counter2].hp <= 0) {
									wallArray[counter2].destroy = true;
								}
							}
						}
						counter2++;
					}
					counter++;
			}

			// ENEMY COLLIDES WITH WALL
			counter = 0;
			for (iteratorE = enemyArray.begin(); iteratorE != enemyArray.end(); iteratorE++) {
				counter2 = 0;
				for (iteratorW = wallArray.begin(); iteratorW != wallArray.end(); iteratorW++) {
					if (enemyArray[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds())) {
						if (enemyArray[counter].direction == 1) {
							enemyArray[counter].canMoveUp = false;
							enemyArray[counter].rect.move(0, 1);
						}
						else if (enemyArray[counter].direction == 2) {
							enemyArray[counter].canMoveDown = false;
							enemyArray[counter].rect.move(0, -1);
						}
						else if (enemyArray[counter].direction == 3) {
							enemyArray[counter].canMoveLeft = false;
							enemyArray[counter].rect.move(1, 0);
						}
						else if (enemyArray[counter].direction == 4) {
							enemyArray[counter].canMoveRight = false;
							enemyArray[counter].rect.move(-1, 0);
						}
					}
					counter2++;
				}
				counter++;
			}

			// PLAYER COLLIDES WITH WALL
			counter = 0;
			for (iteratorW = wallArray.begin(); iteratorW != wallArray.end(); iteratorW++) {
				if (player1.rect.getGlobalBounds().intersects(wallArray[counter].rect.getGlobalBounds())) {
					if (player1.direction == 1) { // UP
						player1.canMoveUp = false;
						player1.rect.move(0, 1);
					}
					else if (player1.direction == 2) { // DWON
						player1.canMoveDown = false;
						player1.rect.move(0, -1);
					}
					else if (player1.direction == 3) { // LEFT
						player1.canMoveLeft = false;
						player1.rect.move(1, 0);
					}
					else if (player1.direction == 4) { // RIGHT
						player1.canMoveRight = false;
						player1.rect.move(-1, 0);
					}
				}
				counter++;
			}

			// PLAYER COLLIDES WITH PICKUP ITEM
			counter = 0;
			for (iteratorC = pickupArray.begin(); iteratorC != pickupArray.end(); iteratorC++) {
				if (player1.rect.getGlobalBounds().intersects(pickupArray[counter].rect.getGlobalBounds())) {
					if (pickupArray[counter].inShop == true) {
						if (player1.gold >= pickupArray[counter].cost) {

							player1.gold -= pickupArray[counter].cost;
							
							if (pickupArray[counter].isPowerUp == true) {
								soundPowerUp.play();
								player1.powerUp = true;
								player1.novaAttack = false;
								pickupArray[counter].destroy = true;
							}
							if (pickupArray[counter].isNovaPowerUp == true) {
								soundNova.play();
								player1.powerUp = false;
								player1.novaAttack = true;
								pickupArray[counter].destroy = true;
							}
							if (pickupArray[counter].isHpShield == true) {
								player1.hp += 10;
								player1.maxHp += 10;
								pickupArray[counter].destroy = true;
							}
						}
					}

					if (pickupArray[counter].inShop == false) {
						if (pickupArray[counter].isCoin == true) {
							soundDropCoin.play();
							player1.gold += pickupArray[counter].coinValue;
							pickupArray[counter].destroy = true;
						}
						if (pickupArray[counter].isPowerUp == true) {
							soundPowerUp.play();
							player1.powerUp = true;
							player1.novaAttack = false;
							pickupArray[counter].destroy = true;
						}
						if (pickupArray[counter].isNovaPowerUp == true) {
							soundNova.play();
							player1.powerUp = false;
							player1.novaAttack = true;
							pickupArray[counter].destroy = true;
						}	
					}
				}
				counter++;
			}

			// ENEMY COLLIDES WITH PLAYER
			if(elapsed2.asSeconds() >= 0.5){
				clock2.restart();
				counter = 0;
				for (iteratorE = enemyArray.begin(); iteratorE != enemyArray.end(); iteratorE++) {
					if (player1.rect.getGlobalBounds().intersects(enemyArray[counter].rect.getGlobalBounds())) {
						soundCollision.play();
						// TEXT DISPLAY
						textDisplay1.text.setString(std::to_string(enemyArray[counter].attackDamage));
						textDisplay1.text.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2,
							player1.rect.getPosition().y - player1.rect.getSize().y / 2);
						textArray.push_back(textDisplay1);

						player1.hp -= enemyArray[counter].attackDamage;
						player1.powerUp = false;
						player1.novaAttack = false;
					}
					counter++;
				}
			}

			// PROJECTILE COLLIDES WITH ENEMIE
			counter = 0;
			for (iteratorP = projectileArray.begin(); iteratorP != projectileArray.end(); iteratorP++) {
				counter2 = 0;
				for (iteratorE = enemyArray.begin(); iteratorE != enemyArray.end(); iteratorE++) {
					if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray[counter2].rect.getGlobalBounds())) {
						soundDamage.play();
						projectileArray[counter].destroy = true;

						// TEXT DISPLAY
						textDisplay1.text.setString(std::to_string(projectileArray[counter].attackDamage));
						textDisplay1.text.setPosition(enemyArray[counter2].rect.getPosition().x + enemyArray[counter2].rect.getSize().x / 2,
													  enemyArray[counter2].rect.getPosition().y - enemyArray[counter2].rect.getSize().y / 2);
						textArray.push_back(textDisplay1);

						enemyArray[counter2].hp -= projectileArray[counter].attackDamage;
						if (enemyArray[counter2].hp <= 0) {
							enemyArray[counter2].alive = false;
						}
					}
					counter2++;
				}
				counter++;
			}

			// DELETE WALL
			counter = 0;
			for (iteratorW = wallArray.begin(); iteratorW != wallArray.end(); iteratorW++) {
				if (wallArray[counter].destroy == true) {
					// DROP COIN
					if (generateRandom(4) == 1) {
						soundOpeningChest.play();
						pickup1.isCoin = true;
						pickup1.isPowerUp = false;
						pickup1.isNovaPowerUp = false;
						pickup1.sprite.setTexture(textureCoin);
						pickup1.rect.setPosition(wallArray[counter].rect.getPosition().x,
												 wallArray[counter].rect.getPosition().y);
						pickupArray.push_back(pickup1);
					}
					// DROP POWER UP
					if (generateRandom(4) == 1) {
						soundOpeningChest.play();
						pickup1.isCoin = false;
						pickup1.isPowerUp = true;
						pickup1.isNovaPowerUp = false;
						pickup1.sprite.setTexture(textureImprovedPowerUp);
						pickup1.rect.setPosition(wallArray[counter].rect.getPosition().x,
												 wallArray[counter].rect.getPosition().y);
						pickupArray.push_back(pickup1);
					}
					// DROP NOVA 
					if (generateRandom(4) == 1) {
						soundOpeningChest.play();
						pickup1.isCoin = false;
						pickup1.isPowerUp = false;
						pickup1.isNovaPowerUp = true;
						pickup1.sprite.setTexture(textureAroundPowerUp);
						pickup1.rect.setPosition(wallArray[counter].rect.getPosition().x,
							wallArray[counter].rect.getPosition().y);
						pickupArray.push_back(pickup1);
					}
					wallArray.erase(iteratorW);
					break;
				}
				counter++;
			}

			// DELETE ENEMY BLOOD
			counter = 0;
			for (iteratorB = bloodArray.begin(); iteratorB != bloodArray.end(); iteratorB++) {
				window.draw(bloodArray[counter].sprite);
				if (bloodArray[counter].alive == false) {
					bloodArray.erase(iteratorB);
					break;
				}
				counter++;
			}

			// DEAD ENEMY
			counter = 0;
			for (iteratorE = enemyArray.begin(); iteratorE != enemyArray.end(); iteratorE++) {
				if (enemyArray[counter].alive == false) {

					// DROP COIN
					if (generateRandom(4) == 1) {
						pickup1.isCoin = true;
						pickup1.isPowerUp = false;
						pickup1.isNovaPowerUp = false;
						pickup1.rect.setPosition(enemyArray[counter].rect.getPosition().x, enemyArray[counter].rect.getPosition().y);
						pickupArray.push_back(pickup1);
					}
					// DROP POWER UP
					if (generateRandom(8) == 1) {
						pickup1.isCoin = false;
						pickup1.isPowerUp = true;
						pickup1.isNovaPowerUp = false;
						pickup1.sprite.setTexture(textureImprovedPowerUp);
						pickup1.rect.setPosition(enemyArray[counter].rect.getPosition().x,
												 enemyArray[counter].rect.getPosition().y);
						pickupArray.push_back(pickup1);
					}
					// DROP NOVA
					if (generateRandom(12) == 1) {
						pickup1.isCoin = false;
						pickup1.isPowerUp = false;
						pickup1.isNovaPowerUp = true;
						pickup1.sprite.setTexture(textureAroundPowerUp);
						pickup1.rect.setPosition(enemyArray[counter].rect.getPosition().x,
												 enemyArray[counter].rect.getPosition().y);
						pickupArray.push_back(pickup1);
					}

					// CREATE ENEMY BLOOD	
					blood1.isBlood = true;
					blood1.rect.setPosition(enemyArray[counter].rect.getPosition());
					bloodArray.push_back(blood1);

					enemyArray.erase(iteratorE);
					break;
				}
				counter++;
			}

			// DESTROY PROJECTILE
			counter = 0;
			for (iteratorP = projectileArray.begin(); iteratorP != projectileArray.end(); iteratorP++) {
				if (projectileArray[counter].destroy == true) {
					projectileArray.erase(iteratorP);
					break;
				}
				counter++;
			}

			// DELETE TEXT
			counter = 0;
			for (iteratorT = textArray.begin(); iteratorT != textArray.end(); iteratorT++) {
				if (textArray[counter].destroy == true) {
					textArray.erase(iteratorT);
					break;
				}
				counter++;
			}

			// DELETE PICKUP ITEMS
			counter = 0;
			for(iteratorC = pickupArray.begin(); iteratorC != pickupArray.end(); iteratorC++) {
				if (pickupArray[counter].destroy == true) {
					pickupArray.erase(iteratorC);
					break;
				}
				counter++;
			}

			// CREATING NPC
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				enemy1.rect.setPosition(generateRandom(window.getSize().x - enemy1.sprite.getGlobalBounds().width), generateRandom(window.getSize().y - enemy1.sprite.getGlobalBounds().height));
				enemyArray.push_back(enemy1);
			}

			// FIRE
			if (elapsed1.asSeconds() >= 0.3) {
				clock1.restart();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					soundShoot.play();
						if (player1.powerUp == true) {
							if (player1.direction == 1) {
								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2 - 15);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);

								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2 - 15,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);

								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2 + 15,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);
							}
							if (player1.direction == 2) {
								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2 - 15);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);

								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2 - 15,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);

								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2 + 15,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);
							}
							if (player1.direction == 3) {
								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2 - 15);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);

								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2 - 15,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);

								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2 + 15,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);
							}
							if (player1.direction == 4) {
								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2 - 15);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);

								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2 - 15,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);

								projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2 + 15,
									player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
								projectile1.direction = player1.direction;
								projectileArray.push_back(projectile1);
							}
						}
						else if (player1.novaAttack == true) {
							projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2,
								player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectile1.direction = 1;
							projectileArray.push_back(projectile1);

							projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2,
								player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectile1.direction = 2;
							projectileArray.push_back(projectile1);

							projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2,
								player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectile1.direction = 3;
							projectileArray.push_back(projectile1);

							projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2,
								player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectile1.direction = 4;
							projectileArray.push_back(projectile1);
						}
						else {
							projectile1.rect.setPosition(player1.rect.getPosition().x + player1.rect.getSize().x / 2 - projectile1.rect.getSize().x / 2,
								player1.rect.getPosition().y + player1.rect.getSize().y / 2 - projectile1.rect.getSize().y / 2);
							projectile1.direction = player1.direction;
							projectileArray.push_back(projectile1);
						}
				}
			}

			// DRAW WALL
			counter = 0;
			for (iteratorW = wallArray.begin(); iteratorW != wallArray.end(); iteratorW++) {
				wallArray[counter].update();
				window.draw(wallArray[counter].sprite);

				counter++;
			}

			// DRAW ENEMY BLOOD
			counter = 0;
			for (iteratorB = bloodArray.begin(); iteratorB != bloodArray.end(); iteratorB++) {
				bloodArray[counter].update();
				window.draw(bloodArray[counter].sprite);

				counter++;
			}

			// DRAW PICKUP ITEMS
			counter = 0;
			for (iteratorC = pickupArray.begin(); iteratorC != pickupArray.end(); iteratorC++) {
				if (pickupArray[counter].inShop == true) {
					window.draw(pickupArray[counter].text);
				}
				pickupArray[counter].update();
				window.draw(pickupArray[counter].sprite);

				counter++;
			}

			// DRAW PROJECTILES
			counter = 0;
			for (iteratorP = projectileArray.begin(); iteratorP != projectileArray.end(); iteratorP++) {
				projectileArray[counter].update();
				window.draw(projectileArray[counter].sprite);

				counter++;
			}

			// DRAW ENEMIES
			counter = 0;
			for (iteratorE = enemyArray.begin(); iteratorE != enemyArray.end(); iteratorE++) {
				enemyArray[counter].text.setString("HP: " + std::to_string(enemyArray[counter].hp) + "/" + std::to_string(enemyArray[counter].maxHp));
				window.draw(enemyArray[counter].text);
				enemyArray[counter].update();
				enemyArray[counter].updateMovement();
				window.draw(enemyArray[counter].sprite);

				counter++;
			}

			// UPDATE PLAYER
			player1.update();
			player1.updateMovement();

			// PLAYER VIEW
			window.setView(view1);
			view1.setCenter(player1.rect.getPosition());
			text.setPosition(player1.rect.getPosition().x - window.getSize().x / 2, player1.rect.getPosition().y - window.getSize().y / 2);

			// DRAW PLAYER
			window.draw(player1.sprite);

			// DRAW TEXT
			counter = 0;
			for (iteratorT = textArray.begin(); iteratorT != textArray.end(); iteratorT++) {
				textArray[counter].update();

				window.draw(textArray[counter].text);
				counter++;
			}

			// HP
			textHp.setString("Hp " + std::to_string(player1.hp) + "/" + std::to_string(player1.maxHp));
			window.draw(textHp);
			textHp.setPosition(player1.rect.getPosition().x - window.getSize().x / 2, player1.rect.getPosition().y - window.getSize().y / 2 + 25);

			// GOLD
			text.setString("Gold: " + std::to_string(player1.gold));
			window.draw(text);
			text.setPosition(player1.rect.getPosition().x - window.getSize().x / 2, player1.rect.getPosition().y - window.getSize().y / 2);

			// DISPLAY WINDOW
			window.display();
		}
		return EXIT_SUCCESS;
	}