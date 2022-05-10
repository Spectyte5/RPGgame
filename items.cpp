#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <filesystem>
#include "Header.h"


//function to give new character a weapon fitting his class
void Item::start_item_c(Character character){

	//vector holding profession names
	std::vector <std::string> prof{ "Mage", "Warrior", "Berserker", "Thief" };


	//assign weapon
	if (character.prof == prof[0]) {
		id = 255;
		type = 0;
		name = "Weak Staff";
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

//save weapon to file
void Item::save_item_c(Character character) {

	//assign directory of file ./Items/Charactername.txt
	std::string sname = character.name;
	std::string filename = "./Items/";
	sname.append(".txt");
	filename.append(sname);
	std::ofstream file;
	file.open(filename.c_str());

	file << id << " " << value << " " << type << " " << damage << std::endl;

	file.close();
};

//function checking equipped weapon from file and assigning damage bonus for battle simulator
void Item::equipped_item_c(Character &character, std::vector <std::string> weaponnames){
	
	std::vector <std::string> startw{ "Weak Staff", "Weak Sword", "Weak Axe", "Weak Bow" };
	std::vector <std::string> types = { "Staff", "Sword", "Axe" ,"Bow" };
	std::string sname = character.name;
	std::string filename = "./Items/";
	sname.append(".txt");
	filename.append(sname);
	std::ifstream file;
	file.open(filename.c_str());
	std::vector <int> table;
	int number = 0;

	//read all stats to vector
	while (file >> number)
	{
		table.push_back(number);
	}

	//take corresponing values from the table vector
	id = table[0];
	value = table[1];
	type = table[2];
	damage = table[3];


	//if character is using a starting weapon, take name from the starting weapon vector:
	if (id == 255) {
		name = startw[0];
	}
	else if (id == 256) {
		name = startw[1];
	}
	else if (id == 257) {
		name = startw[2];
	}
	else if (id == 258) {
		name = startw[3];
	}

	//otherwise take the name from the names vector:
	else {
		name = weaponnames[id];
	}
	//add the weapon damage to the character damage:
		character.dmg += damage;
	};

// display items stats on screen:
void Item::print_item(Character& character) {
	
	//vector with weapon types to be used as: type[id]:
	std::vector <std::string> types = { "Staff", "Sword", "Axe" ,"Bow" };
	std::cout << "\nWeapon Equipped: " << name << "\n Weapon Type: " << types[type] << "\n Weapon Value: " << value << "\n Weapon Damage: " << damage << "\n Character damage with weapon: " << character.dmg << std::endl;
}

//generate random item, that can be dropped after fight:
void Item:: lottery_item(std::vector <std::string> itemnames){
	
	//weapon type is random:
	type = rand() % 4;

	//switch type and assign id corresponding to the type:
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

	//assign name and damage:
	name = itemnames[id];
	damage = rand() % 600;

	//if damage is higher than 300, value is higher than 500:
	if (damage > 300) {
		value = rand() % 100 + 500;
	}
	else {
		value = rand() % 100;
	}
};

//save generated item to the text file:
void Item::create_item() {

	std::string item_name = name;
	std::string filename = "./Items/";
	item_name.append(".txt");
	filename.append(item_name);
	std::ofstream file;
	file.open(filename.c_str());

	file << id << " " << value << " " << type << " " << damage << std::endl;

	file.close();

};

//function to equip better weapon:
void Item::change_item_c(Character& character, std::vector <std::string> types, Item item_dropped) {

	//if stats of the weapon dropped after fight and 
	if (damage < item_dropped.damage && item_dropped.type == type) {

		//remove previous weapon damage from the character so they dont stack....
		character.dmg -= damage;

		//change equipped weapon stats:
		damage = item_dropped.damage;
		id = item_dropped.id;
		name = item_dropped.name;
		type = item_dropped.type;
		value = item_dropped.value;

		std::cout << "Weapon changed: " << std::endl;
	}
	else {
		
		//remove damage even if weapon not changed because equipped weapon function will assign bonus again.
		character.dmg -= damage;
		std::cout << "No Weapon changes: " << std::endl;
	}
}

//Potions constructor
HPpotion::HPpotion(int id, int value, std::string name, int ammount, int hptoadd) {

		this->id = id;
		this->value = value;
		this->name = name;
		this->ammount = ammount;
		this->hptoadd = hptoadd;
}

//save potion to file
void HPpotion::save_potion(Character character) {

	std::string pot_name = "_" + name;
	std::string char_name = character.name;
	std::string filename = "./Items/Potions/";
	pot_name.append(".txt");
	char_name.append(pot_name);
	filename.append(char_name);
	std::ofstream file;
	file.open(filename.c_str());

	file << id << " " << ammount << std::endl;

	file.close();
}

//display potion on screen:
void HPpotion::print_potion() {

	//display only if ammount in inventory is greater than 0:
	if (ammount > 0) {
		std::cout  << " Name: " << name << " Value: " << value << " Hp_bonus: " << hptoadd << " Ammount: " << ammount << std::endl;
	}
}

//read potion's ammount and type from the text file
void HPpotion::read_potion(Character character) {

	std::string pot_name = "_" + name;
	std::string char_name = character.name;
	std::string filename = "./Items/Potions/";
	pot_name.append(".txt");
	char_name.append(pot_name);
	filename.append(char_name);
	std::ifstream file;
	file.open(filename.c_str());
	std::vector <int> table;
	int number = 0;

	while (file >> number)
	{
		table.push_back(number);
	}
	
	//if id is equal to the value from file, ammount = second value from the file
	if (id == table[0]) ammount = table[1];
	
	file.close();
}

//recursive search for a substring in string vector function
void search_codex(std::vector <std::string> codex, std::string name, int& size) {
 
	//if size is bigger than vector size than entry was not found
	if (size >= codex.size()) {
		std::cout << "\nEntry not found!" << std::endl;
	}
	//if line number: size has the name in it, print out codex
	else if (codex[size].find(name)!= std::string::npos) {
		std::cout << "\n" << codex[size] << std::endl;
	}
	//if not found than add 1 to size and call function again
	else { 
		size+=1;
		search_codex(codex, name, size);
	}
}
