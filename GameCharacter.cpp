#include "GameCharacter.h"

GameCharacter::GameCharacter() {}
GameCharacter::GameCharacter(string name_, string tag_, int max_, int attack_, int defense_) :Object(name_, tag_)
{
	this->maxHealth = max_;
	this->currentHealth = max_;
	this->attack = attack_;
	this->defense = defense_;
}

bool GameCharacter::checkIsDead()
{
	if (this->currentHealth <= 0) return true;
	else return false;
}

void GameCharacter::takeDamage(int demage)
{
	this->currentHealth -= demage;
}

/* setter */
void GameCharacter::setMaxHealth(int max_)
{
	this->maxHealth = max_;
}
void GameCharacter::setCurrentHealth(int cur_)
{
	this->currentHealth = cur_;
}
void GameCharacter::setAttack(int attack_)
{
	this->attack = attack_;
}
void GameCharacter::setDefense(int def_)
{
	this->defense = def_;
}

/* getter */
int GameCharacter::getMaxHealth()
{
	return this->maxHealth;
}
int GameCharacter::getCurrentHealth()
{
	return this->currentHealth;
}
int GameCharacter::getAttack()
{
	return this->attack;
}
int GameCharacter::getDefense()
{
	return this->defense;
}
