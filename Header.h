#pragma once
#ifndef HEADER_H
#define HEADER_H

class Stats {
	
	bool levelup = 0;
public:
	int dmg=0;
	int def=0;
	int hp=0;
	int esc=0;
	int XP=0;
	int experience = 0;
	int level = 0;

	//name here is not neccessary for Character class, but needed for Monster class.
	virtual void set_stats(std::string &name) = 0;
	virtual void save_stats(std::string &name) = 0;
	virtual void get_stats(std::string &name) = 0;

	//private member getter and setter:
	void set_levelup(bool x) {
		this->levelup = x;
	}
	 bool get_levelup() {
		return levelup;
	}

	friend struct Item;
};

class Character : public Stats{

	int weapontype;

public:
	std::string name;
	std::string prof;
	int strength;
	int dexterity;
	int endurance;
	int intelligence;
	int charisma;

	virtual void set_stats(std::string &name)override;
	virtual void save_stats(std::string &name)override;
	virtual void get_stats(std::string &name)override;
	void print_stats();

	void set_type(int x) {
		this->weapontype = x;
	}
	int get_type() {
		return weapontype;
	}

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
	void equipped_item_c(Character &character, std::vector <std::string> weaponnames);
	void lottery_item(std::vector <std::string> itemnames);
	void create_item();
	void change_item_c(Character& character, std::vector <std::string> types, Item item_dropped);
	void print_item(Character& character);

};

struct HPpotion : public Item {

	int id = 0;
	int value = 0;
	std::string name = "";
	int hptoadd = 0;
	int ammount = 0;

	HPpotion(int id, int value, std::string name, int ammount, int hptoadd);
	void save_potion(Character character);
	void print_potion();
	void read_potion(Character character);

};

template<class C, class M> class Battlesim{
	public:
		int win = 0;
		void simmulate(C &character, M &monster, std::vector <HPpotion> &potions, Item item);
		void level_up(C &character);
};

//node structure
struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() {
        head = NULL;
    }
    //Add new element at the end of the list
	void push_back(int newElement);
    //Delete first node of the list
	void pop_front();
    //display the content of the list
	void PrintList(std::vector <std::string> monster_enq, std::vector <int> xp);

};

Character create_character();

Character load_character();

void save_character(Character character, std::string& name, std::string& prof);

void available_characters();

std::vector <Monster> generate_monsters(std::vector <int>& monster_id, std::vector <std::string> monsternames);

void save_monsters(std::vector <Monster> monster_list, std::vector <int> monster_id);

void search_codex(std::vector <std::string> codex, std::string name, int& size);

#endif 