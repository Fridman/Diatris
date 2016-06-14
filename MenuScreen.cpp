
#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

/*	Menuscreen implements the screen abstract class. The idea is to create 
	separate environments for which the entities tcan interact. For example, the
	entities utilized on a menu screen are going to interact differently than the
	entities utilized during gameplay even if they are the same objects (e.g. buttons).
*/

MenuScreen::MenuScreen()
{
	_font.loadFromFile("source/fonts/chango.ttf");
	MenuMessage.setString("Click to start!");
	MenuMessage.setFont(_font);
	MenuMessage.setCharacterSize(16);
	MenuMessage.setOrigin(MenuMessage.getLocalBounds().width/2,MenuMessage.getLocalBounds().height/2);
	MenuMessage.setPosition((window_x)/2, (window_y)/2);
	MenuMessage.setColor(sf::Color::Red);
	buttonManager.createButton((window_x)/2-128, (window_y)/2-50, 256, 100, "NewGame");
	lClicked = false;
}

void MenuScreen::getInput(sf::RenderWindow& window)
//Gets all the input information from the player.
{
	lClicked = false;
	mPosition[0] = sf::Mouse::getPosition(window).x;
	mPosition[1] = sf::Mouse::getPosition(window).y;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		lClicked = true;
	}
}

void MenuScreen::update() 
// Updates all the logic involved with this screen.
{
	buttonManager.update(mPosition,lClicked);
	printf("%s\n", buttonManager.signal);
	if (!strcmp(buttonManager.signal,"NewGame")) {
		Game::screen = std::make_shared<GameScreen>();
	}
}

void MenuScreen::render(sf::RenderWindow& window) 
//Renders all of the required information on this screen.
{
	window.draw(MenuMessage);
}

MenuScreen::~MenuScreen(void)
{
}
