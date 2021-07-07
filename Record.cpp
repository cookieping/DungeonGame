#include "Record.h"

Record::Record() {}

void Record::saveToFile(Player* player, vector<Room>& rooms)
{
	ofstream fout_player("player_info.txt", ios::out);
	ofstream fout_room("room_info.txt", ios::out);

	this->savePlayer(player, fout_player);
	this->saveRooms(rooms, fout_room);

	fout_player.close();
	fout_room.close();
}
void Record::loadFromFile(Player* player, vector<Room>& rooms)
{
	ifstream fin_player("player_info.txt", ios::in);
	ifstream fin_room("room_info.txt", ios::in);

	this->loadRooms(rooms, fin_room);
	cout << "load from room_info.txt succeed" << endl;

	this->loadPlayer(player, fin_player, rooms);
	cout << "load from player_info.txt succeed" << endl;

	fin_player.close();
	fin_room.close();
}

void Record::savePlayer(Player* player, ofstream& os)
{
	os << player->getName() << endl << player->getCurrentHealth() << " " << player->getAttack() << " " << player->getDefense() << " ";
	os << player->getCurrentRoom()->getIndex() << " " << player->getPreviousRoom()->getIndex() << " ";

	int item_num = player->getInventory().size();
	os << item_num << " ";
	for (int i = 0; i < item_num; i++)
		os << (player->getInventory())[i].getName() << endl << (player->getInventory())[i].getHealth() << " " << (player->getInventory())[i].getAttack() << " " << (player->getInventory())[i].getDefense();
}
void Record::saveRooms(vector<Room>& rooms, ofstream& os)
{
	int room_num = rooms.size();
	os << room_num << endl;

	for (int i = 0; i < room_num; i++)
	{
		string type_;

		// index
		//os << i << " ";

		// each room's neighbors (up, down, left, right)
		//if (rooms[i].getUpRoom() != NULL) os << rooms[i].getUpRoom()->getIndex() << " ";
		//else os << -1 << " ";

		// isExit
		//os << rooms[i].getIsExit() << " ";

		// object
		int obj_num = rooms[i].getObjects().size();
		os << obj_num << " ";
		for (int j = 0; j < obj_num; j++)
		{
			type_ = rooms[i].getObjects()[j]->getTag();
			os << type_ << " ";
			if (type_ == "Monster")
			{
				Monster* tmp = dynamic_cast<Monster*>(rooms[i].getObjects()[j]);
				os << tmp->getName() << " " << tmp->getCurrentHealth() << " " << tmp->getAttack() << " " << tmp->getDefense() << " ";
			}
			else if (type_ == "Item")
			{
				Item* tmp = dynamic_cast<Item*>(rooms[i].getObjects()[j]);
				os << tmp->getName() << " " << tmp->getHealth() << " " << tmp->getAttack() << " " << tmp->getDefense() << " ";
			}
			else if (type_ == "NPC")
			{
				NPC* tmp = dynamic_cast<NPC*>(rooms[i].getObjects()[j]);
				int item_num = tmp->getCommodity().size();

				os << tmp->getName() << " " << item_num << " ";
				for (int k = 0; k < item_num; k++)
				{
					os << tmp->getCommodity()[k].getName() << " " << tmp->getCommodity()[k].getHealth() << " " << tmp->getCommodity()[k].getAttack() << " " << tmp->getCommodity()[k].getDefense() << " ";
				}
			}
		}
		os << endl;
	}
}

void Record::loadPlayer(Player* player, ifstream& is, vector<Room>& rooms)
{
	string name_, n;
	int  currhealth_, attack_, defense_, curr_index, prev_index, item_num, h, a, d;

	is >> name_ >> currhealth_ >> attack_ >> defense_;
	is >> curr_index >> prev_index >> item_num;

	*player = Player(name_, 500, attack_, defense_);
	player->setCurrentHealth(currhealth_);
	player->setCurrentRoom(&rooms[curr_index]);
	player->setPreviousRoom(&rooms[prev_index]);

	for (int i = 0; i < item_num; i++)
	{
		is >> n >> h >> a >> d;
		Item item(n, h, a, d);
		player->addItem(item); // no need to add state, because the status has already renewed
	}
}
void Record::loadRooms(vector<Room>& rooms, ifstream& is)
{
	int index_, room_num, obj_num;
	//int u, d, l, r; // neighbors
	int oh, oa, od; // objects
	int is_exit;
	string on, type_;

	//
	for (int i = 0; i < 8; i++)
	{
		rooms.push_back(Room(0, i, vector<Object*>()));
	}

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

	rooms[7].setIsExit(1);
	//

	is >> room_num;
	for (int i = 0; i < room_num; i++)
	{
		//is >> index_;
		//is >> u >> d >> l >> r;
		//is >> is_exit;
		is >> obj_num;

		// build objects
		vector<Object*> objects;

		for (int j = 0; j < obj_num; j++)
		{
			is >> type_;
			if (type_ == "Monster")
			{
				is >> on >> oh >> oa >> od;
				Monster* monster = new Monster(on, oh, oa, od);
				objects.push_back(monster);
			}
			else if (type_ == "Item")
			{
				is >> on >> oh >> oa >> od;
				Item* item = new Item(on, oh, oa, od);
				objects.push_back(item);
			}
			else if (type_ == "NPC")
			{
				int item_num, hh, aa, dd;
				string script_, nn;
				vector<Item> commodities;

				is >> on;
				//getline(is, script_);
				script_ = "Do u wanna buy something?";
				is >> item_num;

				for (int k = 0; k < item_num; k++)
				{
					is >> nn >> hh >> aa >> dd;
					commodities.push_back(Item(nn, hh, aa, dd));
				}
				NPC* npc = new NPC(on, script_, commodities);
				objects.push_back(npc);
			}
		}
		//Room room = Room(is_exit, index_, objects);
		rooms[i].setObjects(objects);


		//rooms.push_back(room);
	}
}
