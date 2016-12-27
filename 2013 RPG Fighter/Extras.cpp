#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include "creatures.h"
#include "Mystrings.h"

void pre_wave_shop(hero_data* hero, int full_hp, int wave)
{
	printf("\n\nThat was tough... Now your HP is not full because of that. you have %iHP remaining.", hero->combat.hp);
	
	printf("\n\nThere are a few options you can follow at this point. \n\n-You could give me 100 coins for more potions, in which case you should imput 'b'.\n\n-You could heal yourself (notice you cannot heal and buy in the same wave), in which case you should imput 'h'.\n\n-You could go on with your adventure without any modification in which case you should just imput any other thing.");
	
	printf("\n\nYou currently have %i coins and %i potions, if you try to buy without 100 of them or heal without potions you will be teleported back to the dungeon automatically.\n\n", hero->coins, hero->items.potions);
	getchar();

	char imput;
	scanf("%c", &imput);
	switch (imput)
	{
	case 'b':
	{
		if (hero->coins < 100)
		{
			printf("\n\nWhat? It seems you don't have enough coins... You were even warned... Well, you were the one who chose so back to the dungeon you go.");
			getchar();
			break;
		}
		else
		{
			hero->coins -= 100;
			hero->items.potions += 1;
			printf("\n\nThank you for your purchase. %i coins and %i potions remaining. Now let's go.", hero->coins, hero->items.potions);
			getchar();
			break;
		}
	}
	case 'h':
	{
		if (hero->items.potions < 1)
		{
			printf("\n\nWhat were you trying to heal with? You are out of potions... I will take you back to the dungeon now...");
			getchar();
			break;
		}
		else
		{
			hero->items.potions -= 1;
			hero->combat.hp += 100;
			if (hero->combat.hp > full_hp)
			{
				hero->combat.hp = full_hp;
			}
			printf("\n\nNow you have %iHP. Time to go back.", hero->combat.hp);
			getchar();
			break;
		}
	defaulf:
		{
			printf("\n\nLet's go! the wave #%i is waitting", wave);
			getchar();
		}
	}
	}
}

void midboss_fight(hero_data* hero, monster_data* globin, monster_data* minion_goblin_1, monster_data* minion_goblin_2)
{
	printf("\n\nYou are working really good %s! Feels like you will exterminate those gu-... Eh? What is that? It is similar to the others but... Oh! Oh no... It is not a simple goblin, it is Globin, the infamous hobgoblin! And he is not alone, two goblins are with him!", hero->name);
	getchar();
	printf("\n\nThose guys have been together for a long time now, I am sure they even have an attack pattern.");
	getchar();

	// Enemies stats

	minion_goblin_1->combat.hp				= 1 + rand() % 24;
	minion_goblin_1->combat.attack_min		= rand() % 7;
	minion_goblin_1->combat.attack_max		= minion_goblin_1->combat.attack_min + 5 + rand() % 7;
	minion_goblin_1->combat.armor			= rand() % 3;
	minion_goblin_1->coins					= rand() % 20;
	minion_goblin_1->xp						= 15;
	minion_goblin_1->items.potions			= 0;

	minion_goblin_2->combat.hp				= 1 + rand() % 14;
	minion_goblin_2->combat.attack_min		= rand() % 7;
	minion_goblin_2->combat.attack_max		= minion_goblin_2->combat.attack_min + 5 + rand() % 7;
	minion_goblin_2->combat.armor			= 3 + rand() % 3;
	minion_goblin_2->coins					= rand() % 20;
	minion_goblin_2->xp						= 15;
	minion_goblin_2->items.potions			= 0;

	globin->combat.hp						= 50;
	globin->combat.attack_min				= 10;
	globin->combat.attack_max				= 25;
	globin->combat.armor					= 6;
	globin->coins							= 75;
	globin->xp								= 50;
	globin->items.potions					= 1;

	int alive_enemies = 3;

	while (alive_enemies > 0 && hero->combat.hp > 0) // Hero attacks
	{
		int total_hero_attack = hero->combat.attack_min + rand() % hero->combat.attack_max;
		int damage_to_enemy;
		int attacked_enemy = rand() % 3 + 1;
		int attacked_enemy_armor;
		switch (attacked_enemy)
		{
		case 1:
		{
			attacked_enemy_armor = minion_goblin_1->combat.armor;
			break;
		}
		case 2:
		{
			attacked_enemy_armor = minion_goblin_2->combat.armor;
			break;
		}
		case 3:
		{
			attacked_enemy_armor = globin->combat.armor;
		}
		}
		
		if (attacked_enemy_armor == minion_goblin_1->combat.armor)
		{
			if (minion_goblin_1->combat.hp <= 0)
			{
				printf("\n\nYou missed the attack! Those guys even know how to evade!");
				getchar();
			}
			else
			{
				damage_to_enemy = total_hero_attack - attacked_enemy_armor;
				int crit_chance = rand() % 6;
				if (crit_chance == 5)
				{
					damage_to_enemy *= 2;
				}

				if (damage_to_enemy > 0)
				{
					minion_goblin_1->combat.hp -= damage_to_enemy;
					if (minion_goblin_1->combat.hp < 0)
					{
						minion_goblin_1->combat.hp = 0;
					}
					printf("\n\nYou hit the first goblin henchman for %i! Now his HP is %i.", damage_to_enemy, minion_goblin_1->combat.hp);
					getchar();
				}
				else
				{
					printf("\n\nIs not the time to slack off! You need to hit harder!");
					getchar();
				}

				if (minion_goblin_1->combat.hp <= 0)
				{
					hero->xp += minion_goblin_1->xp;
					hero->coins += minion_goblin_1->coins;
					printf("\n\nGood job, now he is dead!");
					getchar();
				}
			}
		}
		else if (attacked_enemy_armor == minion_goblin_2->combat.armor)
		{
			if (minion_goblin_2->combat.hp <= 0)
			{
				printf("\n\nYou missed the attack! Those guys even know how to evade!");
				getchar();
			}
			else
			{
				damage_to_enemy = total_hero_attack - attacked_enemy_armor;
				int crit_chance = rand() % 6;
				if (crit_chance == 5)
				{
					damage_to_enemy *= 2;
				}
				if (damage_to_enemy > 0)
				{
					minion_goblin_2->combat.hp -= damage_to_enemy;
					if (minion_goblin_2->combat.hp < 0)
					{
						minion_goblin_2->combat.hp = 0;
					}
					printf("\n\nYou hit the second goblin henchman for %i! Now his HP is %i.", damage_to_enemy, minion_goblin_2->combat.hp);
					getchar();
				}
				else
				{
					printf("\n\nIs not the time to slack off! You need to hit harder!");
					getchar();
				}

				if (minion_goblin_2->combat.hp <= 0)
				{
					hero->xp += minion_goblin_2->xp;
					hero->coins += minion_goblin_2->coins;
					printf("\n\nGood job, now he is dead!");
					getchar();
				}
			}
		}
		else
		{
			if (globin->combat.hp <= 0)
			{
				printf("\n\nYou missed the attack! Those guys even know how to evade!");
				getchar();
			}
			else
			{
				damage_to_enemy = total_hero_attack - attacked_enemy_armor;
				int crit_chance = rand() % 6;
				if (crit_chance == 5)
				{
					damage_to_enemy *= 2;
				}
				if (damage_to_enemy > 0)
				{
					globin->combat.hp -= damage_to_enemy;
					if (globin->combat.hp < 0)
					{
						globin->combat.hp = 0;
					}
					printf("\n\nYou hit Globin for %i! Now his HP is %i.", damage_to_enemy, globin->combat.hp);
					getchar();
				}
				else
				{
					printf("\n\nHe has a better armor! You need to hit even harder!");
					getchar();
				}

				if (globin->combat.hp <= 0)
				{
					hero->xp += globin->xp;
					hero->coins += globin->coins;
					printf("\n\nFinally! He fell! Good job!!");
					getchar();
				}
			}
		}

		alive_enemies = 3; // End of fight check

		if (minion_goblin_1->combat.hp <= 0)
		{
			alive_enemies--;
		}
		if (minion_goblin_2->combat.hp <= 0)
		{
			alive_enemies--;
		}
		if (globin->combat.hp <= 0)
		{
			alive_enemies--;
		}

		if (alive_enemies > 0)
		{
			printf("\n\nDo not lower your ward!");
			getchar();
		}

		if (hero->combat.hp > 0) // Enemies attack
		{
			if (minion_goblin_1->combat.hp > 0)
			{
				int attack_of_goblin = minion_goblin_1->combat.attack_min + rand() % (minion_goblin_1->combat.attack_max - minion_goblin_1->combat.attack_min);
				int damage_hero_recieves = attack_of_goblin - hero->combat.armor;
				int crit_chance = rand() % 6;
				if (crit_chance == 5)
				{
					damage_hero_recieves *= 2;
				}

				if (damage_hero_recieves > 0)
				{
					hero->combat.hp -= damage_hero_recieves;
					if (damage_hero_recieves > 0)
					{
						if (hero->combat.hp < 0)
						{
							hero->combat.hp = 0;
						}
						printf("\n\nThe first hencheman hits you for %i! You have %i HP remaining!", damage_hero_recieves, hero->combat.hp);
						getchar();
					}
				}
				else
				{
					printf("\n\nGood job %s. You blocked that goblin's attack perfectly.", hero->name);
					getchar();
				}
			}
		}
		if (hero->combat.hp > 0)
		{
			if (minion_goblin_2->combat.hp > 0)
			{
				int attack_of_goblin = minion_goblin_2->combat.attack_min + rand() % (minion_goblin_2->combat.attack_max - minion_goblin_2->combat.attack_min);
				int damage_hero_recieves = attack_of_goblin - hero->combat.armor;
				int crit_chance = rand() % 6;
				if (crit_chance == 5)
				{
					damage_hero_recieves *= 2;
				}

				if (damage_hero_recieves > 0)
				{
					hero->combat.hp -= damage_hero_recieves;
					if (damage_hero_recieves > 0)
					{
						if (hero->combat.hp < 0)
						{
							hero->combat.hp = 0;
						}
						printf("\n\nThe second hencheman hits you for %i! You have %i HP remaining!", damage_hero_recieves, hero->combat.hp);
						getchar();
					}
				}
				else
				{
					printf("\n\nWell done %s. You blocked that goblin's attack perfectly.", hero->name);
					getchar();
				}
			}
		}
		if (hero->combat.hp > 0)
		{
			if (globin->combat.hp > 0)
			{
				int attack_of_goblin = globin->combat.attack_min + rand() % (globin->combat.attack_max - globin->combat.attack_min);
				int damage_hero_recieves = attack_of_goblin - hero->combat.armor;
				int crit_chance = rand() % 6;
				if (crit_chance == 5)
				{
					damage_hero_recieves *= 2;
				}

				if (damage_hero_recieves > 0)
				{
					hero->combat.hp -= damage_hero_recieves;
					if (damage_hero_recieves > 0)
					{
						if (hero->combat.hp < 0)
						{
							hero->combat.hp = 0;
						}
						printf("\n\nGlobin hits you for %i! You have %i HP remaining!", damage_hero_recieves, hero->combat.hp);
						getchar();
					}
					
				}
				else
				{
					printf("\n\nNice! You blocked Globin's attack perfectly.", hero->name);
					getchar();
				}
			}
		}
	}
}

void final_boss_fight(hero_data* hero, monster_data* wrath, int full_hp)
{
	printf("\n\n9 waves already... You deserve some healing %s. With your strength maybe you could be the one who- No, that would be too much even for you... What? you are saying nothing is too much for you? I appreciate those feelings but... Okay, okay I will believe you. If you are so sure about yourself I will lead you to Wrath's hideout, the strongest monster in the dungeon. Come this way.", hero->name);
	getchar();

	// Pre fight healing
	hero->combat.hp = full_hp;

	// Wrath's stats
	wrath->combat.hp = hero->combat.hp;
	wrath->combat.attack_min = hero->combat.attack_min;
	wrath->combat.attack_max = hero->combat.attack_max;
	wrath->combat.armor = hero->combat.armor;
	wrath->coins = 200;
	wrath->xp = 150;
	wrath->items.potions = 1;

	printf("\n\nThere he is. Do not give him time to react! Attack!!");
	getchar();

	while (hero->combat.hp > 0 && wrath->combat.hp > 0) // Hero attacks
	{
		int total_hero_attack = hero->combat.attack_min + rand() % hero->combat.attack_max;
		int damage_to_wrath = total_hero_attack - wrath->combat.armor;
		int crit_chance = rand() % 6;
		if (crit_chance == 5)
		{
			damage_to_wrath *= 2;
			printf("\n\nCritical hit!");
			getchar();
		}

		if (damage_to_wrath > 0)
		{
			wrath->combat.hp -= damage_to_wrath;
			if (wrath->combat.hp < 0)
			{
				wrath->combat.hp = 0;
			}
			printf("\n\nGood hit %s! He has %i HP left!", hero->name, wrath->combat.hp);
			getchar();

			if (wrath->combat.hp < 11 && wrath->combat.hp > 0)
			{
				printf("\n\nWait, what?! He can also use potions?! He just healed... You will need to weaken him again! There is no other way!");
				getchar();
				wrath->items.potions -= 1;
				hero->items.potions += 1;
				wrath->combat.hp += 50;
				if (wrath->combat.hp > full_hp)
				{
					wrath->combat.hp = full_hp;
				}
			}
		}
		else
		{
			printf("\n\nThose kinds of attacks are useless against that guy, %s. You will have to give it your all next time!", hero->name);
			getchar();
		}

		if (wrath->combat.hp > 0) // Wrath attacks
		{
			printf("\n\nGet ready for his counter attack!");
			getchar();

			int total_wrath_attack = wrath->combat.attack_min + rand() % wrath->combat.attack_max;
			int damage_to_hero = total_wrath_attack - hero->combat.armor;

			if (damage_to_hero > 0)
			{
				int crit_chance = rand() % 6;
				if (crit_chance == 5)
				{
					damage_to_hero *= 2;
					printf("\n\nHe got you well! Critical hit!");
					getchar();
				}
				hero->combat.hp -= damage_to_hero;
				if (hero->combat.hp < 0)
				{
					hero->combat.hp = 0;
				}
				printf("\n\nHe swung his sword towards you! He dealt %i damage to you!", damage_to_hero);
				getchar();
			}
			else
			{
				printf("\n\nGood dodge there! Now do for it!");
				getchar();
			}
		}
	}
}