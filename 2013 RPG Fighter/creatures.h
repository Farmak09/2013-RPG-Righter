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
	int faia_boruto;
	int heal;
	int icicle_fall;
};

struct hero_data
{
	struct spells spells;
	struct bag items;
	char name[10];
	struct combat_data combat;
	int coins;
	int xp;
	int force_of_fright;
	int level;
};

struct monster_data
{
	struct combat_data combat;
	int coins;
	int xp;
	struct bag items;
};


#endif // __CREATURES_H__