#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Menu
{
private:
	int index;
	Text title;
	Text menu[4];
	Texture texture;
	Font font;

public:
	Menu();
	Menu(float, float);

	void draw(RenderWindow&);
	void MoveUp();
	void MoveDown();
	int PressedItem();
};
#endif