#pragma once
#ifndef HEADER_H
#define HEADER_H

class Stats {
	
public:
	int dmg=0;
	int def=0;
	int hp=0;
	int esc=0;
	int XP=0;
	virtual void set_stats(std::string &name) = 0;
	virtual void save_stats(std::string &name) = 0;
	virtual void get_stats(std::string &name) = 0;

	friend struct Item;
};

class Character : public Stats{

public:
	std::string name;
	std::string prof;
	int strength;
	int dexterity;
	int endurance;
	int intelligence;
	int charisma;
	int weapontype;

	virtual void set_stats(std::string &name)override;
	virtual void save_stats(std::string &name)override;
	virtual void get_stats(std::string &name)override;

	Character();

	Character(std::string name, std::string prof, int strength, int dexterity, int endurance, int intelligence, int charisma, int weapontype);


	friend class Mage;
	friend class Warrior;
	friend class Berserker;
	friend class Thief;
};

class Monster : public Character
{
public:
	Monster(std::string monster_name);
	virtual void set_stats(std::string& name)override;
	virtual void get_stats(std::string& name)override;
};

class Mage {
public:
	Character add_boost(Character& character);
};

class Warrior {
public:
	Character add_boost(Character& character);
};

class Berserker {
public:
	Character add_boost(Character& character);
};

class Thief {
public:
	Character add_boost(Character& character);
};

struct Item{

	int id=0;
	int value=0;
	std::string name="";
	int type=0;
	int damage = 0;
	void start_item_c(Character character);
	void save_item_c(Character character);
	void equipped_item_c(Character &character, std::vector <std::string> types);
	void lottery_item(std::vector <std::string> itemnames);
	void create_item();
};

Character create_character();

Character load_character();

void save_character(Character character, std::string& name, std::string& prof);

void available_characters();

std::vector <Monster> generate_monsters(std::vector <int>& monster_id, std::vector <std::string> monsternames);

void save_monsters(std::vector <Monster> monster_list, std::vector <int> monster_id);

#endif 