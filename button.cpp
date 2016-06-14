#include "button.h"


button::button(void)
{
	x = 0;
	y = 0;
	width = 256;
	height = 256;
	strcpy(signal, "");
	mouse[0] = 1;
	mouse[1] = 1;
	pressed = false;
}

button::button(int _x, int _y, int _width, int _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	strcpy(signal, "");
	mouse[0] = 1;
	mouse[1] = 1;
	pressed = false;
}


button::~button(void)
{
}


sf::Sprite button::getSprite() {
	sf::Sprite abc = sf::Sprite();
	return abc;
}

void button::update(bool lClicked) {
	pressed = false;
	strcpy(signal, "");
	if ( lClicked && isClicked( mouse ) ) {
		pressed = true;
		//printf("%i, %i\n", mouse[0], mouse[1]);
		//strcpy(signal, "BUTTON PRESSED\n");
	}
}

bool button::isClicked( int mouse[2] ) {
	//Check to see if a button is clicked.
	if (IS_BETWEEN(mouse[0], x, x+width ) && IS_BETWEEN(mouse[1], y, y+height)) {
		return true;
	} else return false;
}

bool button::operator<(const button& b) const {
    if (y < b.y) {
		return true;
	}
	return false;
}
bool button::operator>(const button& b) const {
    if (y > b.y) {
		return true;
	}
	return false;
}