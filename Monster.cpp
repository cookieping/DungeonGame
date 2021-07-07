#include "Monster.h"

Monster::Monster() {}
Monster::Monster(string name_, int max_, int attack_, int defense_) :GameCharacter(name_, "Monster", max_, attack_, defense_) {}

/* deal with the combat system */
bool Monster::triggerEvent(Object* obj, RenderWindow& window)
{
	Player* player = dynamic_cast<Player*>(obj);

	int demage = 0;
	char choice;
	//cout << "You encounter a monster -- " << this->getName() << "!" << endl;

	// load background & monsters
	Texture texture_room, texture_pig, texture_boss;
	texture_room.loadFromFile("resourses/dungeon_room1.png");
	texture_pig.loadFromFile("resourses/pig.png");
	texture_boss.loadFromFile("resourses/boss1.png");

	Sprite sp_room, sp_pig, sp_boss;
	sp_room.setTexture(texture_room);
	sp_room.scale(Vector2f(1.3, 1.3));
	sp_pig.setTexture(texture_pig);
	sp_pig.scale(Vector2f(0.55, 0.55));
	sp_boss.setTexture(texture_boss);
	sp_boss.scale(Vector2f(0.85, 0.85));

	sp_pig.setPosition(Vector2f(1200 / 4 + 65, 900 / 4));
	sp_boss.setPosition(Vector2f(1200 / 5 - 350, 900 / 5));

	// text
	Font font;
	font.loadFromFile("prstartk.ttf");
	Text title1, title2, select1, select2, killed;

	title1.setString("Encounter monster " + this->getName());
	title2.setString("Choose action");
	select1.setString("Attack");
	select2.setString("Retreat");
	killed.setString("Monster Killed!");

	title1.setFont(font);
	title2.setFont(font);
	select1.setFont(font);
	select2.setFont(font);
	killed.setFont(font);

	title1.setCharacterSize(30);
	title2.setCharacterSize(50);
	select1.setCharacterSize(35);
	select2.setCharacterSize(35);
	killed.setCharacterSize(50);

	title1.setPosition(Vector2f(1200 / 10 + 100, 900 / 6 - 100));
	title2.setPosition(Vector2f(1200 / 2 - 500, 900 / 2 + 200));
	select1.setPosition(Vector2f(1200 / 2 - 500, 900 / 2 + 260));
	select2.setPosition(Vector2f(1200 / 2 - 500, 900 / 2 + 305));
	killed.setPosition(Vector2f(200, 300));

	title1.setFillColor(Color(255, 255, 255, 180));
	title2.setFillColor(Color(255, 255, 255, 180));
	select1.setFillColor(Color(254, 255, 212, 255));
	select2.setFillColor(Color(255, 255, 255, 180));
	killed.setFillColor(Color::Red);

	/* Sounds */
	SoundBuffer buffer1, buffer2, buffer3;
	if (!buffer1.loadFromFile("resourses/audio/boss_yield.wav"))
		cout << "Open the audio error." << endl;
	Sound boss_yield;
	boss_yield.setVolume(50);
	boss_yield.setBuffer(buffer1);

	if (!buffer2.loadFromFile("resourses/audio/pigg.wav"))
		cout << "Open the audio error." << endl;
	Sound pig_yield;
	pig_yield.setVolume(50);
	pig_yield.setBuffer(buffer2);

	if (!buffer3.loadFromFile("resourses/audio/attack.wav"))
		cout << "Open the audio error." << endl;
	Sound attacks;
	attacks.setVolume(50);
	attacks.setBuffer(buffer3);

	int selected = 0;

	while (!player->checkIsDead() && !this->checkIsDead())
	{
		//cout << "!!!debug" << endl;
		// visualize choices
		Event event;
		while (window.isOpen())
		{
			//window.clear();
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::KeyReleased:
					switch (event.key.code)
					{
					case Keyboard::Up:
					case Keyboard::Left:
						select1.setFillColor(Color(254, 255, 212, 255));
						select2.setFillColor(Color(255, 255, 255, 180));
						selected = 0;
						break;
					case Keyboard::Down:
					case Keyboard::Right:
						select1.setFillColor(Color(255, 255, 255, 180));
						select2.setFillColor(Color(254, 255, 212, 255));
						selected = 1;
						break;
					case Keyboard::Return:
						switch (selected)
						{
						case 0: // Attack
							cout << "Choose to attack" << endl;
							attacks.play();
							demage = this->getDefense() - player->getAttack();
							this->setCurrentHealth(this->getCurrentHealth() + demage);

							if (this->checkIsDead())
							{
								cout << "You kill the monster!" << endl;
								window.draw(killed);
								window.display();
								// waiting time
								float timer = 0, limit = 0.5;
								Clock clock;
								while (timer < limit + 0.1)
								{
									float time = clock.getElapsedTime().asSeconds();
									clock.restart();
									timer += time;
								}
								return true;
							}
							else
							{
								// waiting time
								float timer = 0, limit = 0.15;
								Clock clock;
								while (timer < limit + 0.1)
								{
									float time = clock.getElapsedTime().asSeconds();
									clock.restart();
									timer += time;
								}

								sp_pig.scale(Vector2f(1.3, 1.3));
								sp_pig.setPosition(Vector2f(1200 / 4, 900 / 4 - 100));
								sp_boss.scale(Vector2f(1.3, 1.3));
								sp_boss.setPosition(Vector2f(1200 / 5 - 450, 900 / 5 - 100));

								window.clear();
								window.draw(sp_room);
								if (player->getCurrentRoom()->getIndex() == 2) window.draw(sp_pig);
								else if (player->getCurrentRoom()->getIndex() == 7) window.draw(sp_boss);

								window.draw(title1);
								window.draw(title2);
								window.draw(select1);
								window.draw(select2);
								window.display();

								// waiting time
								timer = 0, limit = 0.2;
								while (timer < limit + 0.1)
								{
									float time = clock.getElapsedTime().asSeconds();
									clock.restart();
									timer += time;
								}
								// sounds
								if (player->getCurrentRoom()->getIndex() == 2)
									pig_yield.play();
								if (player->getCurrentRoom()->getIndex() == 7)
									boss_yield.setPlayingOffset(seconds(2.f)), boss_yield.play();

								timer = 0, limit = 0.3;
								while (timer < limit + 0.1)
								{
									float time = clock.getElapsedTime().asSeconds();
									clock.restart();
									timer += time;
								}
								sp_pig.scale(Vector2f(1 / 1.3, 1 / 1.3));
								sp_pig.setPosition(Vector2f(1200 / 4 + 65, 900 / 4));
								sp_boss.scale(Vector2f(1 / 1.3, 1 / 1.3));
								sp_boss.setPosition(Vector2f(1200 / 5 - 350, 900 / 5));

								cout << "You are hit by the monster." << endl;
								demage = player->getDefense() - this->getAttack();
								player->setCurrentHealth(player->getCurrentHealth() + demage);
								if (player->checkIsDead()) return false;
								player->triggerEvent(player, window);
							}
							break;
						case 1: // Retreat
							cout << "Choose to retreat" << endl;
							player->changeRoom(player->getPreviousRoom());
							return false;
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
			window.clear();

			window.draw(sp_room);
			if (player->getCurrentRoom()->getIndex() == 2) window.draw(sp_pig);
			else if (player->getCurrentRoom()->getIndex() == 7) window.draw(sp_boss);

			window.draw(title1);
			window.draw(title2);
			window.draw(select1);
			window.draw(select2);

			window.display();
		}
	}
	return false;
}
