#include "Player.h"

Player::Player() {}
Player::Player(string name_, int max_, int attack_, int defense_) :GameCharacter(name_, "Player", max_, attack_, defense_) {}

void Player::addItem(Item item)
{
	(this->inventory).push_back(item);
}

void Player::increaseStates(int h, int a, int d)
{
	// health
	this->setCurrentHealth(this->getCurrentHealth() + h);
	if (this->getCurrentHealth() > this->getMaxHealth()) this->setCurrentHealth(this->getMaxHealth());

	this->setAttack(this->getAttack() + a);
	this->setDefense(this->getDefense() + d);
}

void Player::changeRoom(Room* room)
{
	this->previousRoom = this->currentRoom;
	this->currentRoom = room;
}

/* show the status of player */
bool Player::triggerEvent(Object* obj, RenderWindow& window)
{
	Player* player = dynamic_cast<Player*>(obj);
	string str[4] = {}, items[5] = {};
	int str_num = 4, item_num = 0;
	str[0] = "[" + player->getName() + "]";
	str[1] = "Health: " + to_string(player->getCurrentHealth()) + " / " + to_string(player->getMaxHealth());
	str[2] = "Attack: " + to_string(player->getAttack());
	str[3] = "Defense: " + to_string(player->getDefense());

	/*
	if ((player->getInventory()).size() != 0)
	{
		for (int i = 0; i < (player->getInventory()).size(); i++) items[i] = (player->getInventory())[i].getName();
		str_num++;
		item_num = player->getInventory().size();
	}*/

	// Visualize the words
	Text text_p, text_h, text_a, text_d;
	Font font;

	font.loadFromFile("prstartk.ttf");
	
	text_p.setFont(font);
	text_p.setString(str[0]);
	text_p.setCharacterSize(25);
	text_p.setPosition(Vector2f(1200 / 2 + 110, 900 / 2 - 330));

	text_h.setFont(font);
	text_h.setString(str[1]);
	text_h.setCharacterSize(25);
	text_h.setPosition(Vector2f(1200 / 2 + 110, 900 / 2 - 290));

	text_a.setFont(font);
	text_a.setString(str[2]);
	text_a.setCharacterSize(25);
	text_a.setPosition(Vector2f(1200 / 2 + 110, 900 / 2 - 250));

	text_d.setFont(font);
	text_d.setString(str[3]);
	text_d.setCharacterSize(25);
	text_d.setPosition(Vector2f(1200 / 2 + 110, 900 / 2 - 210));

	window.draw(text_p);
	window.draw(text_h);
	window.draw(text_a);
	window.draw(text_d);

	window.display();
	
	// showing status
	float timer = 0, limit = 0.6;
	Clock clock;
	while (timer < limit + 0.1)
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
	}

	return true;
}

/* setter */
void Player::setCurrentRoom(Room* r)
{
	(this->currentRoom) = r;
}
void Player::setPreviousRoom(Room* r)
{
	(this->previousRoom) = r;
}
void Player::setInventory(vector<Item> items)
{
	(this->inventory) = items;
}

/* getter */
Room* Player::getCurrentRoom()
{
	return this->currentRoom;
}
Room* Player::getPreviousRoom()
{
	return this->previousRoom;
}
vector<Item> Player::getInventory()
{
	return this->inventory;
}
