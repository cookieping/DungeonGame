#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Dungeon.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
#include "Menu.h"

using namespace std;

int main()
{
	Image image;
	srand(time(0));
	RenderWindow window(VideoMode(1200, 900), "!Dungeon Game!");
	
	Menu menu(window.getSize().x, window.getSize().y);
	Dungeon dungeon = Dungeon();

	Music music;
	if (!music.openFromFile("resourses/audio/dungeon_music.wav"))
		cout << "Open music error." << endl;
	music.setVolume(20);
	music.setLoop(true);
	music.play();

	while (window.isOpen())
	{
		Event event;
		Clock clock;
		float timer = 0, limit = 0.3;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
				case Keyboard::Left:
					menu.MoveUp();
					break;
				case Keyboard::Down:
				case Keyboard::Right:
					menu.MoveDown();
					break;
				case Keyboard::Return:
					switch (menu.PressedItem())
					{
					case 0: // start new game
						cout << "Start New Game..." << endl;
						window.setVisible(false);
						dungeon.runDungeon(0, music);
						window.setVisible(true);
						break;
					case 1: // load record
						cout << "Load Old Game..." << endl;
						window.setVisible(false);
						dungeon.runDungeon(1, music);
						window.setVisible(true);
					case 2: // quit
						window.close();
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
		window.clear();
		menu.draw(window);
		window.display();
	}

	return 0;
}