#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Room.h"
#include "Record.h"

using namespace std;
using namespace sf;

class Dungeon {
private:
	Player player;
	Record record;
	vector<Room> rooms;
	int room_num;

	Texture texture_room, texture_pig, texture_boss, texture_sales,
		texture_shield, texture_sword, texture_win, texture_lose, texture_shadow;
	Texture texture_word;

	Sprite room_sf, pig_sf, boss_sf, sales_sf, shield_sf,
		sword_sf, win_sf, lose_sf, shadow_sf;

	Font font_word;

	Color colors[4];

	int selected = 0;

	float width, height; // window

public:
	Dungeon();
	/* Create a new player, and give him/her basic status */
	void createPlayer();

	/* Create a map, which include several different rooms */
	void createMap();

	/* Deal with player's moveing action */
	void handleMovement(bool, bool, bool, bool, bool, RenderWindow&);

	/* Deal with player's iteraction with objects in that room */
	void handleEvent(Object*, RenderWindow&);

	/* Deal with all game initial setting       */
	/* Including create player, create map etc  */
	void startGame(int load_); // if load_ == 1, load old game

	/* Deal with the player's action     */
	/* including showing the action list */
	/* that player can do at that room   */
	/* and dealing with player's input   */
	void chooseAction(vector<Object*>, RenderWindow&);

	/* Check whether the game should end or not */
	/* Including player victory, or he/she dead */
	bool checkGameLogic(RenderWindow&, Music&);

	/* Deal with the whole game process */
	void runDungeon(int load_, Music&); // if load_ == 1, load old game

	/* For visualize */
	int MoveUp(int, Text*, int);

	int MoveDown(int, Text*, int);
};


#endif // DUNGEON_H_INCLUDED
