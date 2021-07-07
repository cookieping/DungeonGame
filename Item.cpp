#include "Item.h"

Item::Item() :Object() {}
Item::Item(string name_, int health_, int attack_, int defense_) : Object(name_, "Item")
{
	this->health = health_;
	this->attack = attack_;
	this->defense = defense_;
}

/* deal with pick up action, add status to player */
bool Item::triggerEvent(Object* obj, RenderWindow& window)
{
	SoundBuffer buffer;
	if (!buffer.loadFromFile("resourses/audio/ding.wav"))
		cout << "Open the audio error." << endl;
	Sound ding;
	ding.setVolume(50);
	ding.setBuffer(buffer);
	ding.play();

	Player* player = dynamic_cast<Player*>(obj);
	cout << player->getName() << " gets a " << this->getName() << endl;

	player->addItem(*this);
	player->increaseStates(this->getHealth(), this->getAttack(), this->getDefense());

	/* show player's new status */
	cout << player->getName() << "'s status has been renewed." << endl;
	player->triggerEvent(player, window);

	return true;
}

/* Getter */
int Item::getHealth()
{
	return this->health;
}
int Item::getAttack()
{
	return this->attack;
}
int Item::getDefense()
{
	return this->defense;
}

/* Setter */
void Item::setHealth(int h)
{
	this->health = h;
}
void Item::setAttack(int a)
{
	this->attack = a;
}
void Item::setDefense(int d)
{
	this->defense = d;
}
