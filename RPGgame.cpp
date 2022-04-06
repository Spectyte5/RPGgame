#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <filesystem>
#include "Header.h"

int main()
{
	int x = 0;
	Item next_item, eq_item;
	srand((unsigned int)time(NULL));
	std::vector <int> monster_id={0,0,0,0,0};
	std::vector <std::string> types = { "Staff", "Sword", "Axe" ,"Bow" };
	std::vector <std::string> monsternames = {
	"Grimesnare",
	"Venomface",
	"Stenchscream",
	"Nightpest",
	"The Calm Fiend",
	"The Barren Woman",
	"The Parallel Glob",
	"The Masked Cavern Cobra",
	"The Primeval Tomb Fiend",
	"The Arctic Preying Freak",
	"Stinkmirage",
	"Stinktooth",
	"Razorscream"
	"Cavebrute",
	"The Muted Keeper",
	"The Gruesome Screamer",
	"The Electric Deformity",
	"The Onyx Nightmare Serpent",
	"The Evasive Phantom Snake",
	"The Ivory Assassin Gorilla"
	};
	std::vector <std::string> weaponnames = {

		//Bows: 
		"Blinkstrike",
		"Stinger",
		"Retirement",
		"Shadow Strike",
		"Silencer",
		"Stryker",
		"Heartpiercer",
		"Devil's Kiss",
		"Iron Composite Bow",
		"Ironbark Shortbow",
		//Swords
		"Holy Katana",
		"Relentless Warblade",
		"Pride's Greatsword",
		"Needle",
		"The Black Blade",
		"Arcane Swiftblade",
		"Honed Warblade",
		"Godslayer",
		"Gladius",
		"Oathbreaker",
		//Staffs
		"Nightfall",
		"Earthfire",
		"Sanguine",
		"Frostward",
		"Serendipity",
		"Hollow Cane",
		"Spellbinder",
		"Netherbane",
		"Shadowfall",
		"Crucifix",
		//Axes
		"Interrogator",
		"Massacre",
		"Lusting Rapier",
		"Lightbane",
		"Reckoning",
		"Fallen Champion",
		"Blackout",
		"Early Retirement",
		"Warmonger",
		"Haunted Axe"
	};

	std::cout << "Rav's Adventure RPG" << std::endl;
	std::cout << "0. Create new character " << std::endl;
	std::cout << "1. Load character " << std::endl;
	std::cout << "2. Exit game " << std::endl;
	std::cin >> x;

	if (x == 1) {
		available_characters();
		auto current_character = load_character();
		current_character.get_stats(current_character.name);
		eq_item.equipped_item_c(current_character, types);
	}
	else if (x == 2) {
		exit(0);
	}
	else {
		auto current_character =create_character();
		if (current_character.prof == "Mage") {
			Mage currentclass;
			currentclass.add_boost(current_character);
		}
		if (current_character.prof == "Warrior") {
			Warrior currentclass;
			currentclass.add_boost(current_character);
		}
		if (current_character.prof == "Berserker") {
			Berserker currentclass;
			currentclass.add_boost(current_character);
		}
		if (current_character.prof == "Thief") {
			Thief currentclass;
			currentclass.add_boost(current_character);
		}
		save_character(current_character, current_character.name, current_character.prof);
		current_character.set_stats(current_character.name);
		current_character.save_stats(current_character.name);
		eq_item.start_item_c(current_character);
		eq_item.save_item_c(current_character);
		eq_item.equipped_item_c(current_character, types);
	}
	auto monsters = generate_monsters(monster_id, monsternames);
	save_monsters(monsters, monster_id);
	next_item.lottery_item(weaponnames);
	next_item.create_item();

	//rememeber to add locking weapon to drop only if its type agrees with type of class.
}
	
