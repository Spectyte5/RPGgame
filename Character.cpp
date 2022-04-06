#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <filesystem>
#include "Header.h"

	Character::Character() {
		name = "";
		prof = "";
		strength = 0;
		dexterity = 0;
		endurance = 0;
		intelligence = 0;
		charisma = 0;
		weapontype = 0;
	}

	Character::Character(std::string name, std::string prof, int strength, int dexterity, int endurance, int intelligence, int charisma, int weapontype) {
		this->name = name;
		this->prof = prof;
		this->strength = strength;
		this->dexterity = dexterity;
		this->endurance = endurance;
		this->intelligence = intelligence;
		this->charisma = charisma;
		this->weapontype = weapontype;
	}


	void Character::set_stats(std::string &name){

		dmg = 200+strength * 60;
		def = 200+strength * 50 + 20 * endurance;
		hp = 200+endurance * 240;
		XP = 1000 + intelligence * 100;
		esc;

		if (charisma > dexterity) {
			esc = (charisma * 640) / 100;
		}
		else {
			esc = (dexterity * 640) / 100;
		}
	}

	void Character::save_stats(std::string &name) {

		std::string character_name = name;
		std::string filename = "./Character_stats/";
		character_name.append("_stats.txt");
		filename.append(character_name);
		std::ofstream file;
		file.open(filename.c_str());

		file << dmg << " " << def << " " << hp << " " << XP << " " << esc << " " << std::endl;

		std::cout << "\nStats:" << std::endl;
		std::cout << " Damage: " << dmg << "\n Defense: " << def << "\n HP:" << hp << "\n XP per level: " << XP << "\n Escape Chance: " << esc << "%" << std::endl;
		file.close();
	}

	void Character::get_stats(std::string &name) {
		std::vector <int> table;
		std::string character_name = name;
		std::string filename = "./Character_stats/";
		character_name.append("_stats.txt");
		filename.append(character_name);
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
		XP = table[3];
		esc = table[4];

		std::cout << "\nStats:" << std::endl;
		std::cout << " Damage: " << dmg << "\n Defense: " << def << "\n HP: " << hp << "\n XP per level: " << XP << "\n Escape Chance: " << esc << "%" << std::endl;

	}

	Character Mage::add_boost(Character& character) {
		int boost = 2;
		character.intelligence += boost;
		std::cout << "\nYour intelligence bonus from your class: " << boost << std::endl;
		return character;
	}

	Character Warrior::add_boost(Character& character) {
		int boost = 2;
		character.endurance += boost;
		std::cout << "\nYour endurance bonus from your class: " << boost << std::endl;
		return character;
	}

	Character Berserker::add_boost(Character& character) {
		int boost = 2;
		character.strength += boost;
		std::cout << "\nYour strength bonus from your class: " << boost << std::endl;
		return character;
	}

	Character Thief::add_boost(Character& character) {
		int boost = 2;
		character.dexterity += boost;
		std::cout << "\nYour dexterity bonus from your class: " << boost << std::endl;
		return character;
	}

Character create_character() {

	int x = 0;
	int points_spent = 0;
	int points_left = 20;
	std::string character_class;
	std::vector <std::string> disp = { "Strength: \nStrength defines your melee damage and influences HP ammount.", "Dexterity \nDexterity skill your escape chance if you are destined to lose.", "Endurance: \nEndurance skill determines ammount of damage taken and ammount of HP.", "Inteligence: \nInteligence skill defines ammount of XP earned.", "Charisma: \nCharisma determines the merchant sell and buy prizes." };
	std::vector <int> stats = { 0,0,0,0,0 };
	std::vector <std::string> prof{ "Mage", "Warrior", "Berserker", "Thief" };

	for (int i = 0; i < stats.size(); i++) {
		while (std::cout << "Points left: " << points_left << "\nAssign your points:" << disp[i] && !(std::cin >> stats[i]) || (stats[i] > 10) || (points_left < 1 && stats[i] != points_left) || (stats[i] < 0) || (points_spent + stats[i] != 20 && i == 4 && stats[i]!= points_left)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid ammount of points, please try again \n";
		}
		points_left -= stats[i];
		points_spent += stats[i];
	}
	while (std::cout << "\nSkills assigned! Now choose a profession:\n0.Mage\nProfficent in magic and elxir crafting, Mages gain +2 start inteligence and use Staffs.\n1.Warrior\nFearless warriors with high ammount of HP, as true tanks they gain +2 start endurance and use Swords.\n2.Berserker\nMasters of the melee combat and tactics, gain + 2 start strenght and use Axes.\n3.Thief\nHighest damage output of all classes, thiefs are sneaky and deadly, they gain +2 start dexterity and use Bows." && !(std::cin >> x) || (x > prof.size() - 1) || x < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input; please re-enter.\n";
	}

	character_class = prof[x];

	std::string display;
	std::cout << "Name your character: " << std::endl;
	std::cin >> display;

	Character obj(display, character_class, stats[0], stats[1], stats[2], stats[3], stats[4], x);

	return obj;
}


Character load_character() {

	std::vector <std::string> prof{ "Mage", "Warrior", "Berserker", "Thief" };
	std::vector <int> table;
	std::string name;
	std::string filename = "./Saves/";
	std::cout << "Enter name of your character: " << std::endl;
	std::cin >> name;
	std::string display = name;
	display.append(".txt");
	std::ifstream file;
	filename.append(display);
	file.open(filename.c_str());
	int number = 0;

	while (file >> number)
	{
		table.push_back(number);
	}

	int s = table[0];
	int d = table[1];
	int e = table[2];
	int i = table[3];
	int c = table[4];
	int id = table[5];
	int t = table[6];

	std::string y_class = prof[id];

	Character your_character(name, y_class, s, d, e, i, c, t);
	std::cout << "\n" << name << ", Class: " << y_class << ", Attributes: " << std::endl;
	std::cout << " Strength: " << your_character.strength << "\n Dexterity: " << your_character.dexterity << "\n Endurance: " << your_character.endurance << "\n Inteligence: " << your_character.intelligence << "\n Charisma: " << your_character.charisma << std::endl;

	return your_character;

}

void save_character(Character character, std::string& name, std::string& prof) {

	std::string display = name;
	std::string filename = "./Saves/";
	display.append(".txt");
	filename.append(display);
	std::ofstream file;
	file.open(filename.c_str());
	int class_id = 0;

	if (prof == "Mage") {
		class_id = 0;
	}
	if (prof == "Warrior") {
		class_id = 1;
	}
	if (prof == "Berserker") {
		class_id = 2;
	}
	if (prof == "Thief") {
		class_id = 3;
	}

	int weapontype = class_id;

	std::cout << "\n" << name << ", Class: " << prof << ", Attributes: " << std::endl;

	file << character.strength << " " << character.dexterity << " " << character.endurance << " " << character.intelligence << " " << character.charisma << " " << class_id << " " << weapontype << std::endl;
	std::cout << " Strength: " << character.strength << "\n Dexterity: " << character.dexterity << "\n Endurance: " << character.endurance << "\n Inteligence: " << character.intelligence << "\n Charisma: " << character.charisma << std::endl;
	file.close();
}

void available_characters() {

	std::cout << "Characters available: " << std::endl;

	//Improved, because save directory and program directory are the same we can use .:
	const std::filesystem::path path{ ".\\Saves" };
	for (auto const& dir_entry : std::filesystem::directory_iterator{ path }) {
		if (dir_entry.is_regular_file() && dir_entry.path().string().ends_with(".txt")) {
			std::cout << dir_entry.path().filename().replace_extension() << '\n';
		}
	}
}



