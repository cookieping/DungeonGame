#include "NPC.h"

NPC::NPC() {}
NPC::NPC(string name_, string script_, vector<Item> commodity_) :GameCharacter(name_, "NPC", 0, 0, 0)
{
	this->script = script_;
	this->commodity = commodity_;
}

/* print all items int this NPC */
void NPC::listCommodity(int& cnt, Text* items)
{
	cnt = (this->commodity).size();
	for (int i = 0; i < cnt; i++)
	{
		items[i].setString((this->commodity)[i].getName());
	}
	items[cnt].setString("I don't want to buy anything.");
}

/* deal with transaction in easy implementation */
bool NPC::triggerEvent(Object* obj, RenderWindow& window)
{
	char choice;
	int items_num = (this->commodity).size();
	Player* player = dynamic_cast<Player*>(obj);

	Texture texture_room, texture_sales;
	Sprite room_sf, sales_sf;
	texture_room.loadFromFile("resourses/dungeon_room1.png");
	texture_sales.loadFromFile("resourses/sales.png");
	room_sf.setTexture(texture_room);
	room_sf.scale(Vector2f(1.3, 1.3));
	sales_sf.setTexture(texture_sales);
	sales_sf.scale(Vector2f(0.9, 0.9));
	sales_sf.setPosition(Vector2f(1200 / 4 + 50, 900 / 4 + 160));

	Text script, items[5];
	Font font;
	font.loadFromFile("prstartk.ttf");
	int cnt = 0;

	// setstring
	script.setString(this->getScript());
	listCommodity(cnt, items);

	script.setFont(font);
	script.setCharacterSize(40);
	script.setPosition(Vector2f(1200 / 2 - 500, 900 / 2 + 150));
	script.setFillColor(Color(255, 255, 255, 180));
	for (int i = 0; i <= cnt; i++)
	{
		items[i].setFont(font);
		items[i].setCharacterSize(35);
		items[i].setPosition(Vector2f(1200 / 2 - 500, 900 / 2 + 200 + i * 45));
		items[i].setFillColor(Color(255, 255, 255, 180));
	}
	items[0].setFillColor(Color(254, 255, 212, 255));

	int selected = 0;
	Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
				case Keyboard::Left:
					if (selected - 1 >= 0)
					{
						items[selected].setFillColor(Color(255, 255, 255, 180));
						selected--;
						items[selected].setFillColor(Color(254, 255, 212, 255));
					}
					break;
				case Keyboard::Down:
				case Keyboard::Right:
					if (selected + 1 <= cnt)
					{
						items[selected].setFillColor(Color(255, 255, 255, 180));
						selected++;
						items[selected].setFillColor(Color(254, 255, 212, 255));
					}
					break;
				case Keyboard::Return:
					if (selected == cnt) // the player doesn't buy anything
						return false;

					SoundBuffer buffer;
					if (!buffer.loadFromFile("resourses/audio/ding.wav"))
						cout << "Open the audio error." << endl;
					Sound ding;
					ding.setVolume(50);
					ding.setBuffer(buffer);
					ding.play();

					(this->commodity)[selected].triggerEvent(player, window);
					this->commodity.erase(commodity.begin() + selected);
					return false;
					break;
				}
				break;
			case Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();

		window.draw(room_sf);
		window.draw(sales_sf);
		window.draw(script);
		for (int i = 0; i <= cnt; i++) window.draw(items[i]);

		window.display();
	}




	/*cout << this->getScript() << endl;; // "Do you want to buy something?"
	this->listCommodity();

	cin >> choice;
	int num = choice - 'A';
	if (num == items_num) // means that player does not want to buy things
	{
		cout << "Okay..." << endl;
		return false;
	}
	else if (num >= 0 && num < items_num) // means that the player have buy an item
	{
		/* pick up action & the (the item) update the player's state 
		(this->commodity)[num].triggerEvent(player, window);
		this->commodity.erase(commodity.begin() + num);
		return false;
	}*/

	return false; // means that the player neither buy any thing nor choose do not buy
}

/* setter */
void NPC::setScript(string s)
{
	this->script = s;
}
void NPC::setCommodity(vector<Item> items)
{
	this->commodity = items;
}

/* getter */
string NPC::getScript()
{
	return this->script;
}
vector<Item> NPC::getCommodity()
{
	return this->commodity;
}
