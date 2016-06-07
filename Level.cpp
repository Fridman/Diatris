#include "Level.h"


Level::Level(void)
{
	srand(time(NULL));
	comboCount = 1;
	shakeCount = 0;
	shaker[0] = 0;
	shaker[1] = 3;
	shaker[2] = -3;
	shaker[3] = 5;
	shaker[4] = -5;
	shaker[5] = 7;
	shaker[6] = -7;
	shaker[7] = 9;
	shaker[8] = -9;
	points = 0;
	levelCount = 1;
	playerDead = false;
	quickercounter = 0;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 9; j++)
			architecture[j][i] = 0;
	moved = false;
	player_x = 4;
	player_y = 14;
	levelClock.restart();
	updateTime = 900;
	levelTexture.create(9*SCALE_SIZE, 15*SCALE_SIZE);
	blocks.loadFromFile("source/sprites/block.png");
	blocks.setSmooth(true);
	blocksSprite.setScale(.75,.75);
	blocksSprite.setTexture(blocks);
	coins.loadFromFile("source/sprites/coin.png");
	coins.setSmooth(true);
	coinsSprite.setScale(.375,.375);
	coinsSprite.setTexture(coins);
	orbs.loadFromFile("source/sprites/orb.png");
	orbs.setSmooth(true);
	orbsSprite.setTexture(orbs);
	orbsSprite.setScale(.75,.75);
}

void Level::update(ActionList _actionList)
{
	if (levelClock.getElapsedTime().asMilliseconds() >= updateTime) {
		quickercounter += levelClock.getElapsedTime().asMilliseconds();
		levelClock.restart();
		//if (architecture[player_x][player_y+1] == 1)
		player_y--;
		for (int i = 0; i < 14; i++) {
			for (int j = 0; j < 9; j++) {
				architecture[j][i] = architecture[j][i+1];
			}
		}
		fillRow(14); //Fills the bottom row.
	} else if (_actionList.checkAction('l') || _actionList.checkAction('r') || _actionList.checkAction(' ')) {
		if ( !moved && _actionList.checkAction('l') && architecture[player_x-1][player_y] != 1 && player_x > 0)
			player_x--;
		if ( !moved && _actionList.checkAction('r') && architecture[player_x+1][player_y] != 1 && player_x < 8)
			player_x++;
		if ( !moved && _actionList.checkAction(' ')) {
			int coinCount = 0;
			for (int i = player_y+1; i < 15; i++) {
				if (architecture[player_x][i] == 1) {
					if (i == player_y+1) {
						architecture[player_x][i] = 0;
					} else {
						player_y = i-1;
						break;
					}
				} else if (i == 14) {
					playerDead = true;
					player_y = 14;
				}
				else if (architecture[player_x][i] == 2) {
					coinCount++;
					architecture[player_x][i] = 0;
				}
			}
			if (coinCount > 0) {
				shakeCount = coinCount * comboCount;
				if (shakeCount > 9)
					shakeCount = 9;
				points += 10*coinCount*coinCount*comboCount;
				comboCount++;
			} else {
				comboCount = 1;
			}
		}
		moved = true;
	} else {
		moved = false;
	}
	printf("%i\n", levelCount);
	if (quickercounter > 10000) {
		quickercounter = 0;
		updateTime -= updateTime/(levelCount*3);
		levelCount++;
	}

	drawSprites();
	
	if (!IS_BETWEEN(player_y, -1, 16)) {
		playerDead = true;
	}
}

void Level::fillRow(int rowNumber) {
	for (int i = 0; i < 9; i++) {
		architecture[i][rowNumber] = rand() % 3;
		if (architecture[i][rowNumber] != 2) {
			architecture[i][rowNumber] = rand() % 5;
			if (architecture[i][rowNumber] < 4)
				architecture[i][rowNumber] = 0;
			else
				architecture[i][rowNumber] = 2;
		} else {
			architecture[i][rowNumber] = 1;
		}

	}
}

void Level::drawSprites()
	/* Draw all the sprites on the level.
	*/
{
	levelTexture.clear();
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 9; j++) {
			blocksSprite.setPosition(j*SCALE_SIZE, i*SCALE_SIZE);
			if (architecture[j][i] == 1) {
				blocksSprite.setColor(sf::Color::White);
				if (j == player_x && i == player_y+1) {
				blocksSprite.setColor(sf::Color(230,230,230,200));
				}
				levelTexture.draw(blocksSprite);
			} else {
				blocksSprite.setColor(sf::Color(30,30,30,255));
				levelTexture.draw(blocksSprite);
			}
			if (architecture[j][i] == 2) {
				coinsSprite.setPosition(j*SCALE_SIZE+12, i*SCALE_SIZE+12);
				if (i <= player_y) {
					coinsSprite.setColor(sf::Color(30,30,30,255));	
				} else {
					coinsSprite.setColor(sf::Color(255,255,255,255));	
				}
				levelTexture.draw(coinsSprite);
				
			}
		}
		orbsSprite.setPosition(player_x*SCALE_SIZE, player_y*SCALE_SIZE);
		orbsSprite.setColor(sf::Color::White);
		levelTexture.draw(orbsSprite);
	}
	levelTexture.display();
}

sf::Sprite Level::getSprite()
{
	sf::Sprite levelSprite(levelTexture.getTexture());
	levelSprite.setPosition(shaker[shakeCount], 50);
	if (shakeCount > 0) {
		sf::sleep(sf::Time(sf::milliseconds(50)));
		shakeCount--;
	}
	return levelSprite;
}

bool Level::playerLose()
{
	return playerDead;
}

int Level::getCombo()
{
	return comboCount;
}

int Level::getPoints()
{
	return points;
}

Level::~Level(void)
{
}
