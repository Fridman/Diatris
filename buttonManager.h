#pragma once
#include "button.h"

class Signal
{
public:
	Signal(void);
	Signal(char _signal[64]);
	~Signal(void);
	char signal[64];
};

class buttonManager
{
public:
	buttonManager(void);
	~buttonManager(void);
	char signal[64];
	std::map<button,Signal> buttonList;
	void addButton(button _button, Signal _signal);
	void update(int mouse[2], bool lClicked);
	void createButton(int _x, int _y, int _width, int _height, Signal _signal);
};

