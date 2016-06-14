#include "buttonManager.h"

// Signal class encapsulates the signal for the map since maps can't take arrays as values.
Signal::Signal(void)
{
}

// Specifies the signal for each button in the button manager.
Signal::Signal(char _signal[64])
{
	strcpy(signal, _signal);
}

Signal::~Signal(void)
{
}


//buttonManager class keeps track of all the buttons and their signals.
buttonManager::buttonManager(void)
{
	strcpy(signal, "");
}


buttonManager::~buttonManager(void)
{
}

void buttonManager::createButton(int _x, int _y, int _width, int _height, Signal _signal) {
	button _button(_x, _y, _width, _height);
	buttonList[_button] = Signal(_signal);
}

void buttonManager::addButton(button _button, Signal _signal) {
	buttonList[_button] = Signal(_signal);
}

void buttonManager::update(int mouse[2], bool lClicked) {
	strcpy(signal, "");
	std::map<button, Signal>::reverse_iterator it;
	for ( it = buttonList.rbegin(); it != buttonList.rend(); ++it ) {
		button but = it->first;
		but.mouse[0] = mouse[0];
		but.mouse[1] = mouse[1];
		but.update(lClicked);
		if (but.pressed) {
			strcpy(signal, it->second.signal);
		}
	}
}

