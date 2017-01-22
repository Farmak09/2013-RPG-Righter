#ifndef __CREATURES_H__
#define __CREATURES_H__

// find here the manin data structure for the game
// feel free to expand it to suit your improvements

struct combat_data
{
	int hp;
	int attack_min;
	int attack_max;
	int armor;
	int mana;
};

struct bag
{
	int potions;
};

struct spells
{
	int yol_toor_shul;
	int synthesis;
	int icicle_fall;
	int windstrike;
};

struct hero_data
{
	struct spells spells;
	struct bag items;
	char name[10];
	struct combat_data combat;
	int coins;
	int xp;
	int level;
	int AoE;
	int pasive;
	int full_hp;
};

struct monster_data
{
	struct combat_data combat;
	int coins;
	int xp;
	struct bag items;
};


#endif // __CREATURES_H__