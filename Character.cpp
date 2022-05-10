#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <filesystem>
#include "Header.h"


//default constructor for inheritance:
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

	//constructor assiging parameter values to the member values:
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


	//set character stats:
	void Character::set_stats(std::string &name){

		dmg = 200+strength * 60;
		def = 200+strength * 50 + 20 * endurance;
		hp = 200+endurance * 240;
		XP = 1000 + intelligence * 100;

		//escape chance is calculated from the better of the 2 stats:
		if (charisma > dexterity) {
			esc = (charisma * 640) / 100;
		}
		else {
			esc = (dexterity * 640) / 100;
		}
	}

	void Character::print_stats() {
		std::cout << "-------------------------------------------------------------------" << std::endl;
		std::cout << "\nStats:" << std::endl;
		std::cout << " Damage: " << dmg << "\n Defense: " << def << "\n HP:" << hp << "\n XP per level: " << XP << "\n Escape Chance: " << esc << "%" << "\n Current XP: " << experience << "\n Level: " << level << std::endl;

	}

	//save characterstats to the text file and display them on screen:
	void Character::save_stats(std::string &name) {

		std::string character_name = name;
		std::string filename = "./Character_stats/";
		character_name.append("_stats.txt");
		filename.append(character_name);
		std::ofstream file;
		file.open(filename.c_str());

		file << dmg << " " << def << " " << hp << " " << XP << " " << esc << " " << experience << " " << level << " " << std::endl;

		print_stats();

		file.close();
	}

	//read the character stats from the file:
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
		experience = table[5];
		level = table[6];

		print_stats();

	}
	
	//member functions to add attribute boost for each profession: 
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

	//create character function:
Character create_character() {

	//x is choice variable
	int x = 0;
	//points already spent counter
	int points_spent = 0;
	//20 points total
	int points_left = 20;
	std::string character_class;
	std::vector <std::string> disp = { "Strength: \nStrength defines your melee damage and influences Defense ammount.", "Dexterity \nDexterity skill your escape chance if you are destined to lose.", "Endurance: \nEndurance skill determines ammount of HP and Defense you have.", "Inteligence: \nInteligence skill defines ammount of XP earned.", "Charisma: \nCharisma skill increases your ability to distract a monster and escape death." };
	std::vector <int> stats = { 0,0,0,0,0 };
	std::vector <std::string> prof{ "Mage", "Warrior", "Berserker", "Thief" };

	for (int i = 0; i < stats.size(); i++) {

		//loop until the input is correct:
		while (std::cout << "Points left: " << points_left << "\nAssign your points:" << disp[i] && !(std::cin >> stats[i]) || (stats[i] > 10) || (points_left < 1 && stats[i] != points_left) || (stats[i] < 0) || (points_spent + stats[i] != 20 && i == 4 && stats[i]!= points_left)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid ammount of points, please try again \n";
		}
		
		//update points left and spent after each iteration
		points_left -= stats[i];
		points_spent += stats[i];
	}
	//choose profession:
	while (std::cout << "\nSkills assigned! Now choose a profession:\n0.Mage\nProfficent in magic and elxir crafting, Mages gain +2 start inteligence and use Staffs.\n1.Warrior\nFearless warriors with high ammount of HP, as true tanks they gain +2 start endurance and use Swords.\n2.Berserker\nMasters of the melee combat and tactics, gain + 2 start strenght and use Axes.\n3.Thief\nHighest damage output of all classes, thiefs are sneaky and deadly, they gain +2 start dexterity and use Bows." && !(std::cin >> x) || (x > prof.size() - 1) || x < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input; please re-enter.\n";
	}

	//profession name from the vector
	character_class = prof[x];

	//name the character
	std::string display;
	std::cout << "Name your character: " << std::endl;
	std::cin >> display;

	//create object with assigned atributes
	Character obj(display, character_class, stats[0], stats[1], stats[2], stats[3], stats[4], x);

	return obj;
}


//load already created character
Character load_character() {

	std::vector <std::string> prof{ "Mage", "Warrior", "Berserker", "Thief" };
	std::vector <int> table;
	std::string name;
	std::string filename = "./Saves/";

	//opens character file from the inputed name:
	std::cout << "Enter name of your character: " << std::endl;
	std::cin >> name;
	std::string display = name;
	display.append(".txt");
	std::ifstream file;
	filename.append(display);
	//check if file exists:
	file.open(filename.c_str());
	if (!file) {
		std::cout << "Save file does not exist, try again!" << std::endl;
		exit(0);
	}
	int number = 0;
	//read values from txt
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

	//create an object
	Character your_character(name, y_class, s, d, e, i, c, t);
	std::cout << "\n" << name << ", Class: " << y_class << ", Attributes: " << std::endl;
	std::cout << " Strength: " << your_character.strength << "\n Dexterity: " << your_character.dexterity << "\n Endurance: " << your_character.endurance << "\n Inteligence: " << your_character.intelligence << "\n Charisma: " << your_character.charisma << std::endl;

	//return object
	return your_character;

}

//save created character to text file or save changes in already existing one:
void save_character(Character character, std::string& name, std::string& prof) {

	std::string display = name;
	std::string filename = "./Saves/";
	display.append(".txt");
	filename.append(display);
	std::ofstream file;
	file.open(filename.c_str());
	int class_id = 0;

	//use name to assign class id:
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

	//weapon type is corresponding to profession id
	int weapontype = class_id;

	std::cout << "\n" << name << ", Class: " << prof << ", Attributes: " << std::endl;

	//write to file:
	file << character.strength << " " << character.dexterity << " " << character.endurance << " " << character.intelligence << " " << character.charisma << " " << class_id << " " << weapontype << std::endl;
	std::cout << " Strength: " << character.strength << "\n Dexterity: " << character.dexterity << "\n Endurance: " << character.endurance << "\n Inteligence: " << character.intelligence << "\n Charisma: " << character.charisma << std::endl;
	file.close();
}

//find avaible characters in the saves folder:
void available_characters() {

	std::cout << "Characters available: " << std::endl;

	//Because save directory and program directory are the same we can use: "./something"
	const std::filesystem::path path{ ".\\Saves" };

	//looking for all the files with .txt extenstion in the path:
	for (auto const& dir_entry : std::filesystem::directory_iterator{ path }) {
		if (dir_entry.is_regular_file() && dir_entry.path().string().ends_with(".txt")) {
			std::cout << dir_entry.path().filename().replace_extension() << '\n'; //replace_extenstion removes the .txt from the output
		}
	}
}



