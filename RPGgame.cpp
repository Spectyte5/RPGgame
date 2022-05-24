#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include "Header.h"

int main()
{
	//Neccessary variables defined:
	bool keep_playing = 0;
	bool check_history = 0;
	int round_counter = 0;
	srand((unsigned int)time(NULL));
	int x = 0;

	// empty list 
	LinkedList MyList;

	//Create necessary objects:
	Item next_item, eq_item;
	Character current_character;
	Battlesim <Character,Monster> sim;
	HPpotion Less_potion(0, 100, "Lesser Health potion", 0, 20), Std_potion(1, 300, "Standard Health potion", 0, 50), Greater_potion(2, 500, "Greater Health potion", 0, 100), Legendary_potion(3, 1000, "Legendary Health potion", 0, 200);
	
	//Vectors for functions to use
	std::vector <HPpotion> potions;
	std::vector <Monster> monsters;
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
	std::vector < std::string> codex = {
		//Bows
		"Blinkstrike, bow with the highest velocity speed created in Kiltisten by a Smith called Gibbezuar.",
		"Stinger, bow created by a smith in Baltazamar, it is powerful, but needs a lot of force to be used.",
		"Retirement,bow of the Champion of Kiltistem, which he used in his final battle during Sedond brittle bones war.",
		"Shadow Strike, bow used by the league of shadows to assasinate the King of Ventirhire.",
		"Silencer, the quietest bow in the Kingdom of Baltazamar, it was created from the special material called Nackergravior.",
		"Stryker, a improved version of standard Iron Composite bow, with a gold coating.",
		"Heartpiercer, bow used by a woman named Cassandra to kill her husband by shooting him in the heart, hence the name.",
		"Devil's Kiss, bow used by a Scary Female assasin Herolda to kill her targets, the legends says she died from the arrow shot from her own bow.",
		"Iron Composite Bow, a solid human bow made of iron, first one was created, before first brittle bones war.",
		"Ironbark Shortbow, a shorter version of the Iron bow, with more circular shape.",
		//Swords
		"Holy Katana, katana used by the Angel of Verenthian to fight demons brought from hell by the evil Corythious.",
		"Relentless Warblade, a blade used by the human forces in the army of Armithian.",
		"Pride's Greatsword, war of the King Pride, a self-centered ruler of Kirkwerian who, used all of his Kingdom's funds for this gold and diamond covered sword.",
		"Needle, a tiny but strong sword made of amarathian steel.",
		"The Black Blade, blade made of obsidian rock in the town of Baltazamar, really durable.",
		"Arcane Swiftblade, a short sword, that suits fighters who use speed as their highest advantage.",
		"Honed Warblade, a blade used by the league of shadows, for mercy killings.",
		"Godslayer, sword used to kill God Polifion by the Champion of Kiltistem, it was crafted from Nackergravior with use of demon's soul.",
		"Gladius, the most famous sword created by smiths in Baltazamar for the Champion of Dwarfs after he leaded them to victory in a fight for the island of Nin.",
		"Oathbreaker, a famous sword embedded in rock, that can only be used by the worthy for the good causes.",
		//Staffs
		"Nightfall, a staff of the evil Mage capitan Meredith, who got possesed by the demon.",
		"Earthfire, a staff created from a demon soul that burns with a never ending fire.",
		"Sanguine, a basic staff created from the sanguine tree.",
		"Frostward, a weapon from a demon soul that frozes its targets.",
		"Serendipity, a famous staff od Hero of Towertin who freed mages from the Kunovian opression.",
		"Hollow Cane, a standard staff made from the Besulifian forrest wood.",
		"Spellbinder, a staff used by most Armithian spellcasters.",
		"Netherbane, a staff composing of nether core and Nin Island's wood.",
		"Shadowfall, a staff used by the Yousther mage to kill 10 demons in Ferasciel.",
		"Crucifix, one of the staffs of famous Lord Vargemoth, an evil prince of darkness.",
		//Axes
		"Interrogator, an axe used to Interrogate the Spy of Baltazamar after he comitted treason.",
		"Massacre, a weapon used to kill king Pride in the Kirkwerian massacre. ",
		"Lusting Rapier, a powerful weapon made of the nikerbak steel.",
		"Lightbane, a axe created from the light rod and Nackergravior and steel merge.",
		"Reckoning, a weapon from the city of Reckoning, it is made of Red Steel, which gives it it's legendary dark red finish.",
		"Fallen Champion, an axe of the Wiking warrior of Thorfin he died in the war of Baltizmirion.",
		"Blackout, an not really sharp but really heave axe which is used to knockout opponents and give them Blackout.",
		"Early Retirement, a standard axe used by Armithian soldiers.",
		"Warmonger, a standard Axe of human league of shadows Berserkers.",
		"Haunted Axe, an axe stolen by a boy from the God Corythious, that later drove him insane."
		//Monsters
		"Grimesnare, he does not look scary, but he is, grimesnares are a tree looking creatures, with a mouth that could fit another tree.",
		"Venomface, a venom spitting reptile, his venom can burn through rocks.",
		"Stenchscream, all in other worlds screamer, is a demon that screams so hard that your ears bleed. ",
		"Nightpest, wolf alpha, leader of a pack, huge, fast and deadly.",
		"The Calm Fiend, a slender, black creature, that can teleport and is pretty scary.",
		"The Barren Woman, a Big and scary woman with an axe, nothing else to add.",
		"The Parallel Glob, a glob like creature, that spists, green kind of a glue toxin.",
		"The Masked Cavern Cobra, deadliest of the snakes Cavern Cobras can choke its pray or use venom it it's teeth to intoxicate them",
		"The Primeval Tomb Fiend, a cave and tomb hiding spider, deadly and scary, keep away.",
		"The Arctic Preying Freak, a polar bear, strong, hungry and angry bear...",
		"Stinkmirage, stinky Green grease monster, smells ugly and looks ugly.",
		"Stinktooth, bigger version of the Stimkmirage, smells even worse, looks even worse too...",
		"Razorscream, a reptile and tiger crossproduct, probably the most deadly creature in Thuridiam."
		"Cavebrute, a cyclop with one eye, who eats sheep for dinner, best idea is to avoid them.",
		"The Muted Keeper, a quiet tiger like creature, that is a real predator.",
		"The Gruesome Screamer, a stronger type of screamer, even louder.",
		"The Electric Deformity, electric demon, they send electric pulses: brr, brr...",
		"The Onyx Nightmare Serpent a sneaky predator snake, that is great at eating things in one bite",
		"The Evasive Phantom Snake, snakes that glow in the dark and have really strong venom.",
		"The Ivory Assassin Gorilla, an special kind of gorilla with ivory claws and wearing armour and using weapons."
	};
	//vector for list to display xpchanges, and previous monster fought
	std::vector <int> xpchange;
	std::vector <std::string> monster_enq;
	//push all potions to the vector:
	potions.push_back(Less_potion);
	potions.push_back(Std_potion);
	potions.push_back(Greater_potion);
	potions.push_back(Legendary_potion);

	//title screen
	std::cout << "-------------------------------------------------------------------" << std::endl;
	std::cout << "Rav's Adventure RPG" << std::endl;
	std::cout << "0. Create new character " << std::endl;
	std::cout << "1. Load character " << std::endl;
	std::cout << "2. Exit game " << std::endl;
	std::cout << "3. Check Codex " << std::endl;
	std::cout << "-------------------------------------------------------------------" << std::endl;
	std::cin >> x;

	if (x == 1) {
		//show characters already created:
		available_characters();
		//load character chosen
		current_character = load_character();
		//get stats from the file
		current_character.get_stats(current_character.name);
		//equip item from file
		eq_item.equipped_item_c(current_character, weaponnames);
		eq_item.print_item(current_character);

		//read stats for all of the potions:
		for (auto& z : potions) {
			z.read_potion(current_character);
		}
		//save stats for all potions
		for (auto& p : potions) {
			p.save_potion(current_character);
		}
	}
	else if (x == 2) {
		exit(0);
	}
	else if (x == 3) {
		std::string c_name;
		int pos = 0;
		bool yn;

		while (std::cout << "\nYou want to check something in the codex? \n Yes: Press 1\n No: Press 0" && std::cin >> yn && yn == 1) {
			std::cout << "-------------------------------------------------------------------" << std::endl;
			std::cout << "CODEX" << std::endl;
			std::cout << "-------------------------------------------------------------------" << std::endl;
			std::cout << "Weapons:" << std::endl;

			for (auto& n : weaponnames) {
				std::cout << n << std::endl;
			}
			std::cout << "-------------------------------------------------------------------" << std::endl;
			std::cout << "\nMonsters:" << std::endl;

			for (auto& n : monsternames) {
				std::cout << n << std::endl;
			}

			std::cout << "-------------------------------------------------------------------" << std::endl;
			std::cout << "Enter name of weapon or monster you want to see more info about : " << std::endl;
			std::cin >> c_name;
			search_codex(codex, c_name, pos);
			std::cout << "-------------------------------------------------------------------" << std::endl;
			//clear console, name string and position
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			c_name.clear();
			pos = 0;
		}
		exit(0);
	}
	else {
		//character creator:
		current_character =create_character();
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
		//save stats to txt.
		save_character(current_character, current_character.name, current_character.prof);
		//calculate and save stats: dmg, hp... from attributes asssigned.
		current_character.set_stats(current_character.name);
		current_character.level = 1;
		current_character.save_stats(current_character.name);
		//equip start_item_c and save inventory to .txt file
		eq_item.start_item_c(current_character);
		eq_item.save_item_c(current_character);
		eq_item.equipped_item_c(current_character, weaponnames);
		eq_item.print_item(current_character);

		//save stats for a new player of all potions (to be avaible if player obtains them later)
		for (auto& p : potions) {
			p.save_potion(current_character);
		}
	}
	//Random 5 monsters for next 10 rounds generated and saved:
	monsters = generate_monsters(monster_id, monsternames);
	save_monsters(monsters, monster_id);

	//main game loop
	std::cout << "-------------------------------------------------------------------" << std::endl;
	while (std::cout << "\nAre you ready to fight?\n Yes: Press 1 to start fight\n No: Press 0 to quit game" && std::cin >> keep_playing && keep_playing == 1) {
		round_counter++;
		//after every 10 fights, monsters are refreshed:
		if (round_counter == 10) {
			monsters = generate_monsters(monster_id, monsternames);
			save_monsters(monsters, monster_id);
		}
		//Add damage substracted in weapon change function. 
		if (round_counter > 1) {
			current_character.dmg += eq_item.damage;
		}
		//Weapon generator:
		next_item.lottery_item(weaponnames);
		next_item.create_item();

		//Next enemy is chosen:
		Monster current_monster = monsters[rand() % 5];
		//get monster stats:
		current_monster.get_stats(current_monster.name);
		//Save monster name and XP to vector:
		monster_enq.push_back(current_monster.name);
		xpchange.push_back(current_monster.experience);
		//Battle starts:
		sim.simmulate(current_character, current_monster, potions, eq_item);
		
		if (round_counter > 10) {
			MyList.pop_front();
		}
		
		//if battle is won give potion
		if (sim.win == 1) {

			int random;

			//potion indexes: 0, 1, very common, 2, 3 rare:
			if (round_counter % 3 == 0) {
				random = rand() % 4;
				potions[random].ammount += 1;
				potions[random].save_potion(current_character);
			}
			else {
				random = rand() % 2;
				potions[random].ammount += 1;
				potions[random].save_potion(current_character);
			}
		}

		//Save results of the fights to the history (Insert element):
		MyList.push_back(sim.win);

		//Changes to weapon loadout:
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		eq_item.change_item_c(current_character, types, next_item);
		eq_item.save_item_c(current_character);
		eq_item.equipped_item_c(current_character, weaponnames);
		//print weapon
		eq_item.print_item(current_character);
		//Check if ammount of XP provides level up and save character changes:
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		sim.level_up(current_character);
		save_character(current_character, current_character.name, current_character.prof);
		//Save stats without weapon damage:
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		current_character.set_stats(current_character.name);
		current_character.save_stats(current_character.name);
		//display history of current session
		std::cout << "-------------------------------------------------------------------" << std::endl;
		while (std::cout << "\nDo you want to see current session result history? \n Yes: Press 1\n No: Press 0" && std::cin >> check_history && check_history == 1) {
			MyList.PrintList(monster_enq,xpchange);
			std::cout << "-------------------------------------------------------------------" << std::endl;
			break;
		}
	}
}
