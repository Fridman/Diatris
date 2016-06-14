#pragma once
#include <SFML/Graphics.hpp>
#define IS_BETWEEN(a, b, c) (a > b && a < c)
class button
{
public:
	sf::Sprite getSprite();
	int x, y, width, height;
	button(void);
	button(int _x, int _y, int _width, int _height);
	bool operator<(const button& b) const;
	bool operator>(const button& b) const;
	~button(void);
	void update(bool lClicked);
	bool isClicked(int mouse[2]);
	char signal[256];
	bool pressed;
	int mouse[2];
};

