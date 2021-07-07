#include "Menu.h"

Menu::Menu() {};
Menu::Menu(float width, float height)
{
	this->index = 0;
	if (!texture.loadFromFile("resourses/dark.jpg"))
	{
		std::cout << "Fail to load picture" << std::endl;
	}
	if (!font.loadFromFile("prstartk.ttf"))
	{
		std::cout << "Fail to load font" << std::endl;
	}
	

	/* Title */
	title.setFont(font);
	title.setString("DUNGEON\nDUNGEON");
	title.setCharacterSize(120);
	title.setPosition(Vector2f(width / 2 - 400, height / 6));

	/* Other settings */
	for (int i = 0; i < 3; i++)
	{
		menu[i].setFont(font);
		menu[i].setCharacterSize(35);
		menu[i].setFillColor(Color(255, 255, 255, 180));
	}

	menu[0].setFillColor(Color(254, 255, 212, 255));
	menu[0].setString("Start New Game");
	menu[0].setPosition(Vector2f(width / 2 - 230, height / 2 + 110));

	menu[1].setString("Load Record");
	menu[1].setPosition(Vector2f(width / 2 - 180, height / 2 + 160));

	/*menu[2].setString("Instruction");
	menu[2].setPosition(Vector2f(width / 2 - 180, height / 2 + 160));
	*/
	menu[2].setString("Quit");
	menu[2].setPosition(Vector2f(width / 2 - 70, height / 2 + 210));
}

void Menu::draw(RenderWindow &window)
{
	window.clear();
	Sprite b;

	b.setTexture(this->texture);
	window.draw(b);
	window.draw(title);
	for (int i = 0; i < 3; i++) window.draw(menu[i]);
}
void Menu::MoveUp()
{
	if (this->index >= 1)
	{
		menu[this->index].setFillColor(Color(255, 255, 255, 180));
		this->index = this->index - 1;
		menu[this->index].setFillColor(Color(254, 255, 212, 255));
	}
}
void Menu::MoveDown()
{
	if (this->index < 2)
	{
		menu[this->index].setFillColor(Color(255, 255, 255, 180));
		this->index = this->index + 1;
		menu[this->index].setFillColor(Color(254, 255, 212, 255));
	}
}
int Menu::PressedItem()
{
	return this->index;
}