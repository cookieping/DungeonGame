#include "Object.h"

Object::Object() {}
Object::Object(string name_, string tag_)
{
	this->name = name_;
	this->tag = tag_;
}

void Object::setName(string name_)
{
	this->name = name_;
}
void Object::setTag(string tag_)
{
	this->tag = tag_;
}

string Object::getName()
{
	return this->name;
}
string Object::getTag()
{
	return this->tag;
}
