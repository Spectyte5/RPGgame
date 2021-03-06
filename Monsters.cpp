#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <filesystem>
#include "Header.h"

//Monster constructor assigning the values, that are randomized
Monster::Monster(std::string monster_name) {
	int strenght = rand() % 10;
	int dexterity = rand() % 10;
	int endurance = rand() % 10;
	int intelligence = rand() % 10;
	int charisma = rand() % 10;
	this->strength = strenght;
	this->dexterity = dexterity;
	this->endurance = endurance;
	this->intelligence = intelligence;
	this->charisma = charisma;
	this->name = monster_name;
}

//set the monster stats and save them:
void Monster::set_stats(std::string &name) {
	
	dmg = strength * 30+200;
	def = 100 + strength * 50 + 20 * endurance;
	hp = 100 + endurance * 240;
	experience = rand() % 500;
	if (dmg > 500 || hp > 1000 || def > 400) {

		level = rand() % 10 + 15;
	}
	else {
		level = rand() % 10;
	}

	std::string monster_name = name;
	std::string filename = "./Monsters/";
	monster_name.append(".txt");
	filename.append(monster_name);
	std::ofstream file;
	file.open(filename.c_str());

	file << dmg << " " << def << " " << hp << " " << experience << " " << level << std::endl;

	file.close();
}

//get monster stats from file:
void Monster::get_stats(std::string &name){

	std::vector <int> table;
	std::string monster_name = name;
	std::string filename = "./Monsters/";
	monster_name.append(".txt");
	filename.append(monster_name);
	std::ifstream file;
	file.open(filename.c_str());

	int number = 0;

	while (file >> number)
	{
		table.push_back(number);
	}

	dmg = table[0];
	def = table[1];
	hp = table[2];
	experience = table[3];
	level = table[4];

	//print
	std::cout << "\nMonster Encounted: " << name << "\nStats:" << std::endl;
	std::cout << " Damage: " << dmg << "\n Defense: " << def << "\n HP: " << hp << "\n XP reward: " << experience << "\n Level: " << level << std::endl;
}

//generate 5 monsters at a time:
std::vector <Monster> generate_monsters(std::vector <int> &monster_id, std::vector <std::string> monsternames) {

	std::vector <Monster> monster_list;
	std::vector <std::string> m_name = { "0", "1", "2", "3", "4" };
	
	//for loop to pick 5 monsters names and save them in vector and their incremented ids in another vector
	for (int i = 0; i < m_name.size(); i++) {
		int id = rand() % monsternames.size();
		monster_id[i] = id;
		m_name[i] = monsternames[id];
	}

	//create monster objects:
	Monster monster1(m_name[0]);
	Monster monster2(m_name[1]);
	Monster monster3(m_name[2]);
	Monster monster4(m_name[3]);
	Monster monster5(m_name[4]);


	//put monster objects in a vector:
	monster_list.push_back(monster1);
	monster_list.push_back(monster2);
	monster_list.push_back(monster3);
	monster_list.push_back(monster4);
	monster_list.push_back(monster5);

	//set their stats:
	monster1.set_stats(m_name[0]);
	monster2.set_stats(m_name[1]);
	monster3.set_stats(m_name[2]);
	monster4.set_stats(m_name[3]);
	monster5.set_stats(m_name[4]);

	return monster_list;
}

//save id of the 5 monsters available in game at the time:
void save_monsters(std::vector <Monster> monster_list, std::vector <int> monster_id) {

	std::ofstream file("./Monsters/monster_list.txt");

	for (int i = 0; i < monster_list.size(); i++) {
		file << monster_list[i].strength << " " << monster_list[i].dexterity << " " << monster_list[i].endurance << " " << monster_list[i].intelligence << " " << monster_list[i].charisma << " " << monster_id[i] << std::endl;
	}

	file.close();
}
