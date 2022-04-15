#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include "Header.h"

void Battlesim<Character, Monster>::simmulate(Character &character, Monster &monster) {

	//health to revive player later:
	int hold_health = character.hp;
	int i = 0;

	//fight until someones hp reaches 0:
	while (monster.hp >= 0 && character.hp >= 0) {

		i++;
		//i is used to change player each round
			if (i % 2 == 0) {
				std::cout << "\n" << character.name << " Turn:\n" << monster.name << " HP: " << monster.hp << "\nPotential Damage: " << character.dmg << std::endl;
		//random chance for attack to be blocked:		
				if (character.def > rand() % 1000 + monster.strength * 100) {
					std::cout << "\nAttack blocked!" << std::endl;
				}
				else {
					//calculate and display health and damage per hit:
						std::cout << monster.hp << " - " << character.dmg << std::endl;
						monster.hp -= character.dmg;
						if (monster.hp < 0) monster.hp = 0;
						std::cout << "GOT HIM!\nHP after hit: " << monster.hp << std::endl;
				}
			}
			else {
				std::cout << "\n" << monster.name << " Turn:\n" << character.name << " HP: " << character.hp << "\nPotential Damage: " << monster.dmg << std::endl;
				if (monster.def > rand() % 1000 + character.strength * 100) {
					std::cout << "\nAttack blocked!" << std::endl;
				}
				else {	
					std::cout << character.hp << " - " << monster.dmg << std::endl;
					character.hp -= monster.dmg;
					if (character.hp < 0) character.hp = 0;
					std::cout << "GOT HIM!\nHP after hit: " << character.hp << std::endl;
				}
			}
		//Check who won and manage experience:
		if (character.hp == 0 && character.esc-rand() % 100 > 0) {
			std::cout << "\nYou escaped the monster and cheated death!" << "\nNo XP changes."  << std::endl;
			break;
		}
		else if (monster.hp == 0) {
			std::cout << "\nYou won the fight!" << "\nXP gained: " << monster.experience << std::endl;
			character.experience += monster.experience;
			break;
		}
		else if (character.hp == 0) {
			std::cout << "\nYou are Dead!" << "\nXP lost: " << monster.experience << std::endl;
			character.experience -= monster.experience;
			if (character.experience < 0) character.experience = 0;
			break;
		}
		
		//wait for 2s
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	//revive:
	character.hp = hold_health;
}

void Battlesim<Character,Monster>::level_up(Character &character){

	std::vector <int> stats = { 0,0,0,0,0 };
	int points_spent = 0;
	int points_left = 5;
	std::vector <std::string> disp = { "Strength: \nStrength defines your melee damage and influences HP ammount.", "Dexterity \nDexterity skill your escape chance if you are destined to lose.", "Endurance: \nEndurance skill determines ammount of damage taken and ammount of HP.", "Inteligence: \nInteligence skill defines ammount of XP earned.", "Charisma: \nCharisma determines the merchant sell and buy prizes." };

	//if level experienced reached add level and reset XP:
	if (character.experience > 1000 * character.level-character.XP) {

		character.experience = 0;
		character.level += 1;
		std::cout << "\nLevel UP!!! Current Level: " << character.level << std::endl;
		//check if levelup reward stats avaible for 
		if (character.level % 5 == 0) character.levelup = 1;

	}

	if (character.level % 5 == 0 && character.levelup == 1) {

		character.levelup = 0;

		std::cout << "Level Bonus Points are available... \n" << std::endl;

		for (int i = 0; i < stats.size(); i++) {
			while (std::cout << "Points left: " << points_left << "\nAssign your points:" << disp[i] && !(std::cin >> stats[i]) || (stats[i] > 5) || (points_left < 1 && stats[i] != points_left) || (stats[i] < 0) || (points_spent + stats[i] != 5 && i == 4 && stats[i] != points_left)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid ammount of points, please try again \n";
			}
			points_left -= stats[i];
			points_spent += stats[i];
		}
		//assign stats chosen:
		character.strength += stats[0];
		character.dexterity += stats[1];
		character.endurance += stats[2];
		character.intelligence += stats[3];
		character.charisma += stats[4];
	}
}


//fix character damage and weapon saving, add templetaized class!