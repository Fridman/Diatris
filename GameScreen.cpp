#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

/*	Game screen implements the screen abstract class. The idea is to create 
	separate environments for which the entities tcan interact. For example, the
	entities utilized on a menu screen are going to interact differently than the
	entities utilized during gameplay even if they are the same objects (e.g. buttons).
*/

Map * GameScreen::gameMap;

GameScreen::GameScreen(void)
	// Constructor loads the map information from a text document an prepares the gameplay objects.
{
	_font.loadFromFile("source/fonts/chango.ttf");
	MenuMessage.setString("0");
	MenuMessage.setOrigin(0, 8);
	MenuMessage.setPosition(10, 10);
	MenuMessage.setFont(_font);
	MenuMessage.setCharacterSize(32);
	MenuMessage.setColor(sf::Color::Red);
}


void GameScreen::getInput(sf::RenderWindow& window)
	//	GetInput takes input from the user and stores it in a list.
{
	if (KEY_LEFT) {
		actions.appendAction('l');
	}
	if (KEY_RIGHT) {
		actions.appendAction('r');
	}
	if (KEY_SPACE) {
		actions.appendAction(' ');
	}
}

void GameScreen::update()
	//	update takes the list of user input and passes it to the player entity.
	//	The player entity takes the list and performs all the required actions.
	//	The action list is cleared for the next cycle.
	//	Additionally, the other objects also update their data for this cycle.
{
	if (!curLevel.playerLose()) {
		curLevel.update(actions);
		actions.clearActions();
	}
	else {
		if (KEY_ENTER)
			Game::screen = std::make_shared<MenuScreen>();
	}
}

void GameScreen::render(sf::RenderWindow& window)
	//	Render draws all of the game objects to the window.
{

	char uiMessage[256];
	sprintf_s(uiMessage, "%i", curLevel.getPoints());
	MenuMessage.setString(uiMessage);
	MenuMessage.setOrigin(MenuMessage.getLocalBounds().width/2,MenuMessage.getLocalBounds().height/2);
	MenuMessage.setPosition((window_x)/4, 16);
	window.draw(MenuMessage);
	sprintf_s(uiMessage, "%iX", curLevel.getCombo());
	MenuMessage.setString(uiMessage);
	MenuMessage.setOrigin(MenuMessage.getLocalBounds().width/2,MenuMessage.getLocalBounds().height/2);
	MenuMessage.setPosition((window_x)/4*3, 16);
	window.draw(MenuMessage);
	window.draw(curLevel.getSprite());
	if (curLevel.playerLose()) {
		MenuMessage.setString("   YOU LOSE\n\nPRESS ENTER\n  TO RETURN");
		MenuMessage.setOrigin(MenuMessage.getLocalBounds().width/2,MenuMessage.getLocalBounds().height/2);
	MenuMessage.setPosition((window_x)/2, (window_y)/2);
		window.draw(MenuMessage);
	}
}

GameScreen::~GameScreen(void)
	//	The destructor is empty for now.
{
}
