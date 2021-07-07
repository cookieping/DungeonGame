#include "Dungeon.h"


/* Visualize */
Dungeon::Dungeon() {};

/* start */
void Dungeon::runDungeon(int load_, Music& music1)
{
	RenderWindow window(VideoMode(1200, 900), "Dungeon Dungeon");

	width = window.getSize().x;
	height = window.getSize().y;

	this->startGame(load_);
	
	texture_room.loadFromFile("resourses/dungeon_room1.png");
	texture_pig.loadFromFile("resourses/pig.png");
	texture_boss.loadFromFile("resourses/boss1.png");
	texture_sales.loadFromFile("resourses/sales.png");
	texture_shield.loadFromFile("resourses/shield.png");
	texture_sword.loadFromFile("resourses/sword.png");
	texture_win.loadFromFile("resourses/win.jfif");
	texture_lose.loadFromFile("resourses/dark.jpg");
	texture_shadow.loadFromFile("resourses/shadow.png");

	room_sf.setTexture(texture_room);
	room_sf.scale(Vector2f(1.3, 1.3));
	pig_sf.setTexture(texture_pig);
	pig_sf.scale(Vector2f(0.55, 0.55));
	boss_sf.setTexture(texture_boss);
	boss_sf.scale(Vector2f(0.85, 0.85));
	sales_sf.setTexture(texture_sales);
	sales_sf.scale(Vector2f(0.9, 0.9));
	shield_sf.setTexture(texture_shield);
	shield_sf.scale(Vector2f(0.3, 0.3));
	sword_sf.setTexture(texture_sword);
	sword_sf.scale(Vector2f(0.5, 0.5));
	win_sf.setTexture(texture_win);
	lose_sf.setTexture(texture_lose);
	shadow_sf.setTexture(texture_shadow);

	pig_sf.setPosition(Vector2f(width / 4 + 65, height / 4));
	boss_sf.setPosition(Vector2f(width / 5 - 350, height / 5));
	sales_sf.setPosition(Vector2f(width / 4 + 50, height / 4 + 160));
	shield_sf.setPosition(Vector2f(width / 4 + 110, height / 4 + 90));
	sword_sf.setPosition(Vector2f(width / 2 - 130, height / 2 - 90));
	win_sf.setPosition(Vector2f(width / 4, height / 4));
	lose_sf.setPosition(Vector2f(width / 4, height / 4));
	shadow_sf.setPosition(Vector2f(width / 4, height / 4));

	colors[0] = Color(254, 255, 212, 255);
	colors[1] = colors[2] = colors[3] = Color(255, 255, 255, 180);

	font_word.loadFromFile("prstartk.ttf");

	SoundBuffer buffer;
	if (!buffer.loadFromFile("resourses/audio/satan_voice.wav"))
		cout << "Open the audio error." << endl;
	Sound tmp;
	tmp.setVolume(50);
	tmp.setBuffer(buffer);
	tmp.play();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		window.draw(room_sf);
		window.display();
		while (this->checkGameLogic(window, music1))
		{
			this->chooseAction(player.getCurrentRoom()->getObjects(), window);
		}

		window.clear();
		window.draw(room_sf);
		window.display();
	}
}

/* Initialize */
void Dungeon::createPlayer()
{
	string name_;
	cout << "Hello! Welcome to Dungeon!\n Please enter your name:  ";
	name_ = "test_player";
	cin >> name_;

	/* health: 500, attack: 100, defense: 50 */
	player = Player(name_, 500, 100, 50);
}

void Dungeon::createMap()
{
	for (int i = 0; i < 8; i++)
	{
		rooms.push_back(Room(0, i, vector<Object*>()));
	}

	// initial player's room
	player.setCurrentRoom(&rooms[0]);
	player.setPreviousRoom(NULL);

	// initialize all rooms' directions
	rooms[0].setRightRoom(&rooms[1]);
	rooms[1].setLeftRoom(&rooms[0]);
	rooms[1].setRightRoom(&rooms[2]);
	rooms[1].setDownRoom(&rooms[3]);
	rooms[2].setLeftRoom(&rooms[1]);
	rooms[3].setUpRoom(&rooms[1]);
	rooms[3].setDownRoom(&rooms[4]);
	rooms[4].setUpRoom(&rooms[3]);
	rooms[4].setLeftRoom(&rooms[5]);
	rooms[4].setRightRoom(&rooms[6]);
	rooms[5].setRightRoom(&rooms[4]);
	rooms[6].setLeftRoom(&rooms[4]);
	rooms[6].setRightRoom(&rooms[7]);
	rooms[7].setLeftRoom(&rooms[6]);

	// set exit
	rooms[7].setIsExit(true);

	//set game characters in the rooms
	vector<Object*> obj;

	Monster* monster1 = new Monster("Peppa_Pig", 100, 80, 20);
	obj = rooms[2].getObjects();
	obj.push_back(monster1);
	rooms[2].setObjects(obj);

	string scripts = "Do u wanna buy something?";
	vector<Item> commodities;
	commodities.push_back(Item("Apple_Pie", 50, 0, 0));
	commodities.push_back(Item("Knife", 0, 30, 0));
	commodities.push_back(Item("Ramen", 100, 0, 0));
	NPC* npc = new NPC("Meow", scripts, commodities);
	obj = rooms[3].getObjects();
	obj.push_back(npc);
	rooms[3].setObjects(obj);

	Item* item1 = new Item("Shield", 0, 0, 20);
	obj = rooms[5].getObjects();
	obj.push_back(item1);
	rooms[5].setObjects(obj);

	Item* item2 = new Item("Cool_Sword", 0, 30, 0);
	obj = rooms[6].getObjects();
	obj.push_back(item2);
	rooms[6].setObjects(obj);

	Monster* monster2 = new Monster("Bad_Boss", 600, 150, 30);
	obj = rooms[7].getObjects();
	obj.push_back(monster2);
	rooms[7].setObjects(obj);
}

void Dungeon::startGame(int load_)
{
	if (load_ == 0) // start new game
	{
		this->createPlayer();
		this->createMap();
	}
	else if (load_ == 1) // load old record
	{
		record.loadFromFile(&player, rooms);
		cout << "...load from file succeed" << endl;
	}
}

/* choose action */
void Dungeon::chooseAction(vector<Object*> objects, RenderWindow &window)
{
	char choice;
	int obj_num = objects.size(), cnt = 3;
	bool has_sales, has_sword, has_shield, has_pig, has_boss;
	has_sales = has_sword = has_shield = has_pig = has_boss = false;

	/* print actions which can be chosen */
	// store the options into the array
	string actions_string[4] = {};
	actions_string[0] = "Move";
	actions_string[1] = "Check my status";
	actions_string[2] = "Save to file";

	for (int i = 0; i < obj_num; i++)
	{
		if ((objects[i])->getTag() == "NPC")
		{
			actions_string[3] = "Talk to NPC " + (objects[i])->getName();
			cnt++;
			has_sales = true;
		}
		if ((objects[i])->getTag() == "Monster")
		{
			actions_string[3] = "Fight with monster " + (objects[i])->getName();
			cnt++;
			if ((objects[i])->getName() == "Peppa_Pig") has_pig = true;
			if ((objects[i])->getName() == "Bad_Boss") has_boss = true;
		}
		if ((objects[i])->getTag() == "Item")
		{
			actions_string[3] = "Pick up item " + (objects[i])->getName();
			cnt++;
			if ((objects[i])->getName() == "Cool_Sword") has_sword = true;
			if ((objects[i])->getName() == "Shield") has_shield = true;
		}
	}

	// visualize the words
	Text title;
	Text actions[4];
	
	title.setFont(font_word);
	title.setString("Choose Action");
	title.setCharacterSize(50);
	title.setPosition(Vector2f(width / 2 - 500, height / 2 + 140));

	for (int i = 0; i < cnt; i++)
	{
		actions[i].setFont(font_word);
		actions[i].setCharacterSize(35);
		actions[i].setFillColor(colors[i]);
		actions[i].setString(actions_string[i]);
		actions[i].setPosition(Vector2f(width / 2 - 500, height / 2 + 200 + i * 45));
	}

	Event event;
	//cout << "debug" << endl;
	while (window.pollEvent(event))
	{
		if (player.checkIsDead()) return;
		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Up:
			case Keyboard::Left:
				selected = MoveUp(selected, actions, cnt);
				break;
			case Keyboard::Down:
			case Keyboard::Right:
				selected = MoveDown(selected, actions, cnt);
				break;
			case Keyboard::Return:
				switch (selected)
				{
				case 0: // Move
					cout << "Choose to move" << endl;
					handleMovement(has_pig, has_boss, has_sword, has_shield, has_sales, window);
					break;
				case 1: // Check my status
					player.triggerEvent(&player, window);
					chooseAction(objects, window);
					break;
				case 2: // Save to file
					record.saveToFile(&player, rooms);
					break;
				case 3: // Handle event
					this->handleEvent(objects[0], window);
					break;
				default:
					break;
				}
				break;
			}
			break;
		case Event::Closed:
			window.close();
			break;
		}
	}

	if (player.checkIsDead()) return;

	window.clear();
	// scene
	window.draw(room_sf);
	if (has_pig) window.draw(pig_sf);
	else if (has_boss) window.draw(boss_sf);
	else if (has_sales) window.draw(sales_sf);
	else if (has_sword) window.draw(sword_sf);
	else if (has_shield) window.draw(shield_sf);

	// text
	window.draw(title);
	for (int i = 0; i < cnt; i++)
	{
		window.draw(actions[i]);
	}
	window.display();
}

void Dungeon::handleMovement(bool has_p, bool has_b, bool has_sw, bool has_sh, bool has_sale, RenderWindow& window)
{
	int cnt = 0, dir, flag = 0;
	char c, dirs[4] = {};
	string str_dir[4] = {};

	/* ask player to choose a direction */
	//cout << "Which direction do you want to move?" << endl;
	if (player.getCurrentRoom()->getUpRoom() != NULL)
	{
		//cout << (char)('A' + cnt) << ". Up" << endl;
		dirs[cnt] = 'u';
		str_dir[cnt] = "Up";
		cnt++;
	}
	if (player.getCurrentRoom()->getRightRoom() != NULL)
	{
		//cout << (char)('A' + cnt) << ". Right" << endl;
		dirs[cnt] = 'r';
		str_dir[cnt] = "Right";
		cnt++;
	}
	if (player.getCurrentRoom()->getDownRoom() != NULL)
	{
		//cout << (char)('A' + cnt) << ". Down" << endl;
		dirs[cnt] = 'd';
		str_dir[cnt] = "Down";
		cnt++;
	}
	if (player.getCurrentRoom()->getLeftRoom() != NULL)
	{
		//cout << (char)('A' + cnt) << ". Left" << endl;
		dirs[cnt] = 'l';
		str_dir[cnt] = "Left";
		cnt++;
	}

	// Visualize text
	Text title, text_dir[4];
	Font font;
	font.loadFromFile("prstartk.ttf");

	title.setFont(font);
	title.setCharacterSize(50);
	title.setPosition(Vector2f(width / 2 - 500, height / 2 + 140));

	for (int i = 0; i < cnt; i++)
	{
		text_dir[i].setFont(font);
		text_dir[i].setCharacterSize(35);
		text_dir[i].setFillColor(colors[i]);
		text_dir[i].setString(str_dir[i]);
		text_dir[i].setPosition(Vector2f(width / 2 - 500, height / 2 + 200 + i * 45));
	}

	/* player choose a direction */
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
					selected = MoveUp(selected, text_dir, cnt);
					break;
				case Keyboard::Down:
				case Keyboard::Right:
					selected = MoveDown(selected, text_dir, cnt);
					break;
				case Keyboard::Return:
					//cout << "**debug" << endl;
					if (dirs[selected] == 'u') player.changeRoom(player.getCurrentRoom()->getUpRoom());
					else if (dirs[selected] == 'r') player.changeRoom(player.getCurrentRoom()->getRightRoom());
					else if (dirs[selected] == 'd') player.changeRoom(player.getCurrentRoom()->getDownRoom());
					else if (dirs[selected] == 'l') player.changeRoom(player.getCurrentRoom()->getLeftRoom());
					flag = 1;
					break;
				}
				break;
			case Event::Closed:
				window.close();
				break;
			}
		}

		window.clear();
		
		// scene
		window.draw(room_sf);
		if (has_p) window.draw(pig_sf);
		else if (has_b) window.draw(boss_sf);
		else if (has_sale) window.draw(sales_sf);
		else if (has_sw) window.draw(sword_sf);
		else if (has_sh) window.draw(shield_sf);

		// text
		window.draw(title);
		for (int i = 0; i < cnt; i++)
		{
			window.draw(text_dir[i]);
		}
		window.display();
		if (flag) break;
	}
}

void Dungeon::handleEvent(Object* obj, RenderWindow& window) // return true means need to pop object
{
	Item* item = dynamic_cast<Item*>(obj);
	if (item != NULL)
	{
		if (item->triggerEvent(&player, window)) // if true, means that the item is picked
		{
			player.getCurrentRoom()->popObject(obj);
			if (player.getCurrentRoom()->getIndex() == 5) // shield
			{
				shield_sf.setPosition(Vector2f(1200 / 2 - 300, 1000));
			}
			if (player.getCurrentRoom()->getIndex() == 6) // sword
			{
				sword_sf.setPosition(Vector2f(1200 / 2 + 300, 1000));
			}
		}
		return;
	}
	Monster* monster = dynamic_cast<Monster*>(obj);
	if (monster != NULL)
	{
		if (monster->triggerEvent(&player, window)) // if true, means that the monster is killed.
		{
			if (!player.getCurrentRoom()->getIsExit()) // cannot pop out the boss room, because still need to judge game logic
			{
				player.getCurrentRoom()->popObject(obj);
			}
			if (player.getCurrentRoom()->getIndex() == 2) // pig
			{
				pig_sf.setPosition(Vector2f(1200 / 2 + 300, 1000));
			}
			if (player.getCurrentRoom()->getIndex() == 7) // boss
			{
				boss_sf.setPosition(Vector2f(1200 / 2 + 300, 1000));
			}
		}
		return;
	}
	NPC* npc = dynamic_cast<NPC*>(obj);
	if (npc != NULL)
	{
		SoundBuffer buffer;
		if (!buffer.loadFromFile("resourses/audio/cat.wav"))
			cout << "Open the audio error." << endl;
		Sound meow;
		meow.setVolume(50);
		meow.setBuffer(buffer);
		meow.play();
		
		npc->triggerEvent(&player, window);
		return;
	}
	// no need to consider "player" condition
	return;
}

/* check game logic */
bool Dungeon::checkGameLogic(RenderWindow &window, Music& music1)
{
	if (player.checkIsDead())
	{
		Texture texture_lose;
		texture_lose.loadFromFile("resourses/dark.jpg");
		Sprite lose;
		lose.setTexture(texture_lose);
		
		Text text_lose;
		Font font;
		font.loadFromFile("prstartk.ttf");

		text_lose.setFont(font);
		text_lose.setString("Game Over");
		text_lose.setCharacterSize(120);
		text_lose.setPosition(Vector2f(width / 2 - 500, height / 6 + 50));
		text_lose.setFillColor(Color::Red);

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
					case Keyboard::Return:
						window.close();
						break;
					default:
						break;
					}
					break;
				case Event::Closed:
					window.close();
					break;
				default:
					break;
				}
			}
			window.clear();
			window.draw(lose);
			window.draw(text_lose);
			window.display();
		}
		cout << "lose" << endl;
		return false;
	}
	if (player.getCurrentRoom()->getIsExit())
	{
		Monster* boss = dynamic_cast<Monster*>(player.getCurrentRoom()->getObjects()[0]);
		if (boss != NULL && boss->checkIsDead()) // victory
		{
			music1.stop();

			Texture texture_win;
			texture_win.loadFromFile("resourses/win.jpg");
			Sprite win;
			win.setTexture(texture_win);

			Text text_win;
			Font font;
			font.loadFromFile("prstartk.ttf");

			text_win.setFont(font);
			text_win.setString("Victory");
			
			text_win.setCharacterSize(120);
			text_win.setPosition(Vector2f(width / 2 - 400, height / 6));
			text_win.setFillColor(Color::Yellow);

			Event event;

			Music music;
			if (!music.openFromFile("resourses/audio/victory.wav"))
				cout << "Open music error." << endl;
			music.setVolume(20);
			music.setLoop(true);
			music.play();

			while (window.isOpen())
			{
				while (window.pollEvent(event))
				{
					switch (event.type)
					{
					case Event::KeyReleased:
						switch (event.key.code)
						{
						case Keyboard::Return:
							window.close();
							break;
						default:
							break;
						}
						break;
					case Event::Closed:
						window.close();
						break;
					default:
						break;
					}
				}
				window.clear();
				window.draw(win);
				window.draw(text_win);
				window.display();
			}
			return false;
		}
	}
	return true; // keep playing
}

int Dungeon::MoveUp(int index_, Text* selection, int num)
{
	if (index_ - 1 >= 0)
	{
		selection[index_].setFillColor(Color(255, 255, 255, 180));
		colors[index_] = Color(255, 255, 255, 180);
		index_--;
		selection[index_].setFillColor(Color(254, 255, 212, 255));
		colors[index_] = Color(254, 255, 212, 255);
	}
	return index_;
}
int Dungeon::MoveDown(int index_, Text* selection, int num)
{
	if (index_ + 1 < num)
	{
		selection[index_].setFillColor(Color(255, 255, 255, 180));
		colors[index_] = Color(255, 255, 255, 180);
		index_++;
		selection[index_].setFillColor(Color(254, 255, 212, 255));
		colors[index_] = Color(254, 255, 212, 255);
	}
	return index_;
}