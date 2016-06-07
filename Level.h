#pragma once
#include "entity.h"
#include "Game.h"

class Level :
	public Entity
{
public:
	Level(void);
	bool playerLose();
	void update(ActionList _actionList);
	int getPoints();
	int getCombo();
	sf::Sprite getSprite();
	~Level(void);

private:
	sf::RenderTexture levelTexture;

	int quickercounter;

	int architecture[9][15];
	int shaker[9];
	int shakeCount;
	int comboCount;
	int player_x;
	int player_y;
	int updateTime;
	int points;
	bool moved;
	bool playerDead;

	int levelCount;

	sf::Clock levelClock;

	sf::Texture blocks;
	sf::Sprite blocksSprite;
	sf::Texture coins;
	sf::Sprite coinsSprite;
	sf::Texture orbs;
	sf::Sprite orbsSprite;


	void fillRow(int rowNumber);
	void drawSprites();

};

