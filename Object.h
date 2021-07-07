#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using namespace sf;

class Object
{
private:
	string name;
	string tag;
public:
	Object();
	Object(string, string);

	/* pure virtual function */
	virtual bool triggerEvent(Object*, RenderWindow&) = 0;

	/* Set & Get function*/
	void setName(string);
	void setTag(string);
	string getName();
	string getTag();
};

#endif
