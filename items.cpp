#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <filesystem>
#include "Header.h"

void Item::start_item_c(Character character){

	std::vector <std::string> prof{ "Mage", "Warrior", "Berserker", "Thief" };
	std::vector <std::string> startw{ "Weak Staff", "Weak Sword", "Weak Axe", "Weak Bow" };

	if (character.prof == prof[0]) {
		id = 255;
		type = 0;
		name = "Weak Stuff";
		value = 0;
		damage = 250;
	}
	if (character.prof == prof[1]) {
		id = 256;
		type = 1;
		name = "Weak Sword";
		value = 0;
		damage = 250;
	}
	if (character.prof == prof[2]) {
		id = 257;
		type = 2;
		name = "Weak Axe";
		value = 0;
		damage = 250;
	}
	if (character.prof == prof[3]) {
		id = 258;
		type = 3;
		name = "Weak Bow";
		value = 0;
		damage = 250;
	}
};

void Item::save_item_c(Character character) {

	std::string sname = character.name;
	std::string filename = "./Items/";
	sname.append(".txt");
	filename.append(sname);
	std::ofstream file;
	file.open(filename.c_str());

	file << id << " " << value << " " << type << " " << damage << std::endl;

	file.close();
};

void Item::equipped_item_c(Character &character, std::vector <std::string> types){
	
	std::string sname = character.name;
	std::string filename = "./Items/";
	sname.append(".txt");
	filename.append(sname);
	std::ifstream file;
	file.open(filename.c_str());
	std::vector <int> table;

	int number = 0;

	while (file >> number)
	{
		table.push_back(number);
	}

	id = table[0];
	value = table[1];
	type = table[2];
	damage = table[3];

	if (id < 250) {
		name = types[id];
	}
		character.dmg += damage;

		std::cout << "\nWeapon Equipped: " << name << "\n Weapon Type: " << types[type] << "\n Weapon Value: " << value << "\n Weapon Damage: " << damage << "\n Character damage with weapon: " << character.dmg << std::endl;
};

void Item:: lottery_item(std::vector <std::string> itemnames){
	
	type = rand() % 4;

	switch (type) {
	case 0:
		id = rand()%10;
		break;
	case 1:
		id = rand()%10 + 10;
		break;
	case 2:
		id = rand()%10 + 20;
		break;
	case 3:
		id = rand()%10 + 30;
		break;
	}

	name = itemnames[id];
	damage = rand() % 600;
	
	if (damage > 300) {
		value = rand() % 100 + 500;
	}
	else {
		value = rand() % 100;
	}
};

void Item::create_item(){

	std::string item_name = name;
	std::string filename = "./Items/";
	item_name.append(".txt");
	filename.append(item_name);
	std::ofstream file;
	file.open(filename.c_str());
	
	file << id <<  " " << value <<  " "  << type << " " << damage << std::endl;

	file.close();

};
