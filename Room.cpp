#include "Room.h"

Room::Room()
{
	this->rightRoom = NULL;
	this->leftRoom = NULL;
	this->upRoom = NULL;
	this->downRoom = NULL;
	this->isExit = false;
	this->index = 0;
	this->objects = vector<Object*>();
}
Room::Room(bool isExit_, int index_, vector<Object*> obj)
{
	this->rightRoom = NULL;
	this->leftRoom = NULL;
	this->upRoom = NULL;
	this->downRoom = NULL;
	this->isExit = isExit_;
	this->index = index_;
	this->objects = obj;
}

/* pop out the specific object when the interaction is done */
bool Room::popObject(Object* obj)
{
	vector<Object*>::iterator it = find((this->objects).begin(), (this->objects).end(), obj);
	if (it == (this->objects).end())
		return false; // fail to pop out
	else
	{
		(this->objects).erase(it);
		return true; // succeed to pop out
	}
}

/* setter */
void Room::setUpRoom(Room* r)
{
	(this->upRoom) = r;
}
void Room::setDownRoom(Room* r)
{
	(this->downRoom) = r;
}
void Room::setLeftRoom(Room* r)
{
	(this->leftRoom) = r;
}
void Room::setRightRoom(Room* r)
{
	(this->rightRoom) = r;
}
void Room::setIsExit(bool b)
{

	(this->isExit) = b;
}
void Room::setIndex(int i)
{
	(this->index) = i;
}
void Room::setObjects(vector<Object*> obj)
{
	(this->objects) = obj;
}

/* getter */
bool Room::getIsExit()
{
	return this->isExit;
}
int Room::getIndex()
{
	return this->index;
}
vector<Object*> Room::getObjects()
{
	return this->objects;
}
Room* Room::getUpRoom()
{

	return this->upRoom;
}
Room* Room::getDownRoom()
{
	return this->downRoom;
}
Room* Room::getLeftRoom()
{
	return this->leftRoom;
}
Room* Room::getRightRoom()
{
	return this->rightRoom;
}

