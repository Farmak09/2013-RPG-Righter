#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include "creatures.h"
#include "Mystrings.h"

void reberu_appu(hero_data* hero)
{
	if (hero->xp >= 90 * hero->level)
	{
		hero->combat.hp				+= 25;
		hero->full_hp				+= 25;
		hero->combat.attack_min		+= 4;
		hero->combat.attack_max		+= 4;
		hero->combat.armor			+= 2;
		hero->combat.mana			+= 15;
		hero->xp					-= 90 * hero->level;
		hero->level++;
		printf("Level Up!! Your stats have increased and now you are level %i!", hero->level);
		getchar();
	}
}

void gob_stats(monster_data* goblin, hero_data* hero)
{
	goblin->combat.hp			= (1 + rand() % 25) + (10 * hero->level);
	goblin->combat.attack_min	= (1 + rand() % 5) + (2 * hero->level);
	goblin->combat.attack_max	= (goblin->combat.attack_min + 5 + rand() % 7) + (3 * hero->level);
	goblin->combat.armor		= rand() % 4 + (2 * hero->level);
	goblin->coins				= rand() % 26;
	goblin->xp					= 15 + 5 * hero->level;
	if (rand() % 6 == 5)
	{
		goblin->items.potions	= 1;
	}
	else
	{
		goblin->items.potions	= 0;
	}
}

void pre_wave_shop(hero_data* hero, int wave)
{
	printf("\n\nThat was tough... You have %iHP remaining.", hero->combat.hp);
	
	printf("\n\nThere are a few options you can follow at this point. \n\n-You could give me 100 coins for more potions (notice you will heal and buy in the same wave), in which case you should imput 'b'.\n\n-You could heal yourself, in which case you should imput 'h'.\n\n-You could buy an item to increase one of your stats, in which case imput 's' to buy a sword and indrease your attack (200 coins), 'a' to increase your armor's efficiency (250 coins), 'c' to raise your maximum health capability (250 coins). \n\nTo on with your adventure without any modification in which case you should just imput any other thing.");
	
	printf("\n\nYou currently have %i coins and %i potions, if you try to buy without 100 of them or heal without potions you will be teleported back to the dungeon automatically.\n\n", hero->coins, hero->items.potions);

	char imput;
	scanf("%c", &imput);
	switch (imput)
	{
	case 'b':
	{
		if (hero->coins < 100)
		{
			printf("\n\nWhat? It seems you don't have enough coins... You were even warned... Well, you were the one who chose so drink whatever you already have.");
			getchar();
		}
		else
		{
			hero->coins -= 100;
			hero->items.potions += 1;
			printf("\n\nThank you for your purchase. %i coins remaining. Now drink it.", hero->coins, hero->items.potions);
			getchar();
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
			hero->combat.hp += 50;
			if (hero->combat.hp > hero->full_hp)
			{
				hero->combat.hp = hero->full_hp;
			}
			printf("\n\nNow you have %iHP. Time to go back.", hero->combat.hp);
			getchar();
			break;
		}
	}
	case 's':
	{
		if (hero->coins >= 200)
		{
			printf("\n\nThank you for your patronage. Your damage has increased thanks to this.");
			getchar();
			hero->combat.attack_min += 5;
			hero->combat.attack_max += 10;
			hero->coins -= 250;
			break;
		}
		else
		{
			printf("\n\nNot enough money");
			getchar();
			break;
		}
	}
	case 'a':
	{
		if (hero->coins >= 250)
		{
			hero->combat.armor += 3;
			hero->coins -= 250;
			printf("\n\nThank you for your patronage. Your armor has increased thanks to this.");
			getchar();
			break;
		}
		else
		{
			printf("\n\nNot enough money");
			getchar();
			break;
		}
	}
	case 'c':
	{
		if (hero->coins >= 250)
		{
			hero->full_hp += 50;
			hero->coins -= 250;
			printf("\n\nThank you for your patronage. Your life points have increased thanks to this.");
			getchar();
			break;
		}
		else
		{
			printf("\n\nNot enough money");
			getchar();
			break;
		}
	}
	default:
	{
		printf("\n\nLet's go! the wave #%i is waitting", wave);
		getchar();
	}
	}
}

int hero_attacking_calculations(hero_data* hero, monster_data* enemy)
{
	int damage_dealt = 0;
	int menu_imput;
	if (hero->spells.yol_toor_shul == 1)
	{
		printf("\n\nUSE A SPELL(1)  MELEE ATTACK(2)\n\n");
		scanf("%i", &menu_imput);

		switch (menu_imput)
		{
		case 1:
		{
			printf("\n\nWhich spell do you want to use?");
			printf("\n\nYol Toor Shul(1)");
			if (hero->spells.synthesis == 1)
			{
				printf("\n\nSynthesis(2)");
			}
			if (hero->spells.icicle_fall == 1)
			{
				printf("\n\nIcicle Fall(3)");
			}
			if (hero->spells.windstrike == 1)
			{
				printf("\n\nWindstrike(4)");
			}
			int spell_imput;
			scanf("%i", &spell_imput);
			switch (spell_imput)
			{
			case 1:
			{
				if (hero->combat.mana >= 25)
				{
					damage_dealt = (hero->combat.attack_max + (hero->combat.attack_max * (1 / 2)) - enemy->combat.armor);
					hero->combat.mana -= 25;
					break;
				}
				else
				{
					printf("\n\nNot enough mana");
					damage_dealt = hero_attacking_calculations(hero, enemy);
				}
			}
			case 2:
			{
				if (hero->combat.mana >= 50)
				{
					hero->combat.hp += 75 + 15 * hero->level;
					if (hero->combat.hp > hero->full_hp)
					{
						hero->combat.hp = hero->full_hp;
					}
					hero->combat.mana -= 50;
					hero->pasive = 1;
					break;
				}
				else
				{
					printf("\n\nNot enough mana");
					damage_dealt = hero_attacking_calculations(hero, enemy);
				}
			}
			case 3:
			{
				if (hero->combat.mana >= 35)
				{
					damage_dealt = (hero->combat.attack_max / 2);
					hero->AoE = 1;
					hero->combat.mana -= 35;
					break;
				}
				else
				{
					printf("\n\nNot enough mana");
					damage_dealt = hero_attacking_calculations(hero, enemy);
				}
			}
			case 4:
			{
				if (hero->combat.mana >= 30)
				{
					damage_dealt = 0;
					for (int i = 0; i <= 1; i++)
					{
						int single_damage_dealt = hero->combat.attack_min + (rand() % (hero->combat.attack_max - hero->combat.attack_min));
						if (rand() % 6 == 0)
						{
							single_damage_dealt *= 2;
							printf("\n\nCritical Hit!");
							getchar();
						}
						damage_dealt += single_damage_dealt - enemy->combat.armor;
					}
					break;
				}
				else
				{
					printf("\n\nNot enough mana");
					damage_dealt = hero_attacking_calculations(hero, enemy);
				}
			}
			default:
			{
				printf("\n\nUNVALID IMPUT");
				damage_dealt = hero_attacking_calculations(hero, enemy);
			}
			}
		}
		case 2:
		{
			break;
		}
		default:
		{
			damage_dealt = hero_attacking_calculations(hero, enemy);
		}
		}
	}
	else
	{
		damage_dealt = (hero->combat.attack_min + (rand() % (hero->combat.attack_max - hero->combat.attack_min))) - enemy->combat.armor;
		if (rand() % 6 == 0)
		{
			damage_dealt *= 2;
			printf("\n\nCritical Hit!");
			getchar();
		}
	}
	return damage_dealt;
}

void midboss_fight(hero_data* hero, monster_data* globin, monster_data* minion_goblin_1, monster_data* minion_goblin_2)
{
	printf("\n\nYou are working really good %s! Feels like you will exterminate those gu-... Eh? What is that? It is similar to the others but... Oh! Oh no... It is not a simple goblin, it is Globin, the infamous hobgoblin! And he is not alone, two goblins are with him!", hero->name);
	getchar();
	printf("\n\nThose guys have been together for a long time now, I am sure they even have an attack pattern.");
	getchar();

	// Enemies stats

	minion_goblin_1->combat.hp				= (1 + rand() % 25) + 10 * hero->level;
	minion_goblin_1->combat.attack_min		= (rand() % 7) + 2 * hero->level;
	minion_goblin_1->combat.attack_max		= (minion_goblin_1->combat.attack_min + 3 + rand() % 7) + 3 * hero->level;
	minion_goblin_1->combat.armor			= (rand() % 3) + 2 * hero->level;
	minion_goblin_1->coins					= rand() % 20;
	minion_goblin_1->xp						= 15 + 5 * hero->level;
	minion_goblin_1->items.potions			= 0;

	minion_goblin_2->combat.hp				= (1 + rand() % 14) + 10 * hero->level;
	minion_goblin_2->combat.attack_min		= (rand() % 7) + 2 * hero->level;
	minion_goblin_2->combat.attack_max		= (minion_goblin_2->combat.attack_min + 3 + rand() % 7) + 3 * hero->level;
	minion_goblin_2->combat.armor			= (rand() % 3) + 2 * hero->level;
	minion_goblin_2->coins					= rand() % 20;
	minion_goblin_2->xp						= 15 + 5 * hero->level;
	minion_goblin_2->items.potions			= 0;

	globin->combat.hp						= 60 + 10 * hero->level;
	globin->combat.attack_min				= 1 + 3 * hero->level;
	globin->combat.attack_max				= 15 + 5 * hero->level;
	globin->combat.armor					= 6 + 3 * hero->level;
	globin->coins							= 75;
	globin->xp								= 50 + 10 * hero->level;
	globin->items.potions					= 0;

	int alive_enemies = 3;

	while (alive_enemies > 0 && hero->combat.hp > 0) // Hero attacks
	{
		int total_hero_attack = hero->combat.attack_min + rand() % (hero->combat.attack_max - hero->combat.attack_min);
		int damage_to_enemy;
		int attacked_enemy;
		for (int i = 0; i == 0; i)
		{
			attacked_enemy = rand() % 3 + 1;
			if (attacked_enemy == 1)
			{
				if (minion_goblin_1->combat.hp > 0)
				{
					i = 1;
				}
			}
			if (attacked_enemy == 2)
			{
				if (minion_goblin_2->combat.hp > 0)
				{
					i = 1;
				}
			}
			if (attacked_enemy == 3)
			{
				if (globin->combat.hp > 0)
				{
					i = 1;
				}
			}
		}
		if (attacked_enemy == 1)
		{
			if (minion_goblin_1->combat.hp <= 0)
			{
				printf("\n\nYou missed the attack! Those guys even know how to evade!");
				getchar();
			}
			else
			{
				damage_to_enemy = total_hero_attack - minion_goblin_1->combat.armor;

				int crit_chance = rand() % 6; // Critical hit
				if (crit_chance == 5)
				{
					damage_to_enemy *= 2;
					printf("\n\nCritical Hit!");
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
		else if (attacked_enemy == 2)
		{
			if (minion_goblin_2->combat.hp <= 0)
			{
				printf("\n\nYou missed the attack! Those guys even know how to evade!");
				getchar();
			}
			else
			{
				damage_to_enemy = total_hero_attack - minion_goblin_2->combat.armor;

				int crit_chance = rand() % 6; // Critical hit
				if (crit_chance == 5)
				{
					damage_to_enemy *= 2;
					printf("\n\nCritical Hit!");
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
				damage_to_enemy = total_hero_attack - globin->combat.armor;

				int crit_chance = rand() % 6; // Critical hit
				if (crit_chance == 5)
				{
					damage_to_enemy *= 2;
					printf("\n\nCritical Hit!");
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

		// Enemies attack   

		if (hero->combat.hp > 0) // minion 1 attacks
		{
			if (minion_goblin_1->combat.hp > 0)
			{
				int attack_of_goblin = minion_goblin_1->combat.attack_min + rand() % (minion_goblin_1->combat.attack_max - minion_goblin_1->combat.attack_min);
				int damage_hero_recieves = attack_of_goblin - hero->combat.armor;

				int crit_chance = rand() % 6; // Critical hit
				if (crit_chance == 5)
				{
					damage_hero_recieves *= 2;
					printf("\n\nHe landed a Critical Hit!");
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

		if (hero->combat.hp > 0) // minion 2 attacks
		{
			if (minion_goblin_2->combat.hp > 0)
			{
				int attack_of_goblin = minion_goblin_2->combat.attack_min + rand() % (minion_goblin_2->combat.attack_max - minion_goblin_2->combat.attack_min);
				int damage_hero_recieves = attack_of_goblin - hero->combat.armor;

				int crit_chance = rand() % 6; // Critical hit
				if (crit_chance == 5)
				{
					damage_hero_recieves *= 2;
					printf("\n\nHe landed a Critical Hit!");
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

		if (hero->combat.hp > 0) // globin attacks
		{
			if (globin->combat.hp > 0)
			{
				int attack_of_goblin = globin->combat.attack_min + rand() % (globin->combat.attack_max - globin->combat.attack_min);
				int damage_hero_recieves = attack_of_goblin - hero->combat.armor;

				int crit_chance = rand() % 6; // Critical hit
				if (crit_chance == 5)
				{
					damage_hero_recieves *= 2;
					printf("\n\nHe landed a Critical Hit!");
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

void final_boss_fight(hero_data* hero, monster_data* wrath)
{
	printf("\n\n9 waves already... You deserve some healing %s. With your strength maybe you could be the one who- No, that would be too much even for you... What? you are saying nothing is too much for you? I appreciate those feelings but... Okay, okay I will believe you. If you are so sure about yourself I will lead you to Wrath's hideout, the strongest monster in the dungeon. Come this way.", hero->name);
	getchar();

	// Pre fight healing
	hero->combat.hp = hero->full_hp;

	// Wrath's stats
	wrath->combat.hp = hero->combat.hp;
	wrath->combat.attack_min = hero->combat.attack_min;
	wrath->combat.attack_max = hero->combat.attack_max;
	wrath->combat.armor = hero->combat.armor;
	wrath->coins = 200;
	wrath->xp = 150 + 20 * hero->level;
	wrath->items.potions = 1;

	printf("\n\nThere he is. Do not give him time to react! Attack!!");
	getchar();
	
	while (hero->combat.hp > 0 && wrath->combat.hp > 0) // Hero attacks
	{
		int total_hero_attack = hero->combat.attack_min + rand() % hero->combat.attack_max;
		int damage_to_wrath = total_hero_attack - wrath->combat.armor;

		int crit_chance = rand() % 6; // Critical hit
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
			printf("\n\nGood hit %s! %i damage dealt! He has %i HP left!", hero->name, damage_to_wrath, wrath->combat.hp);
			getchar();

			if (wrath->combat.hp < 11 && wrath->combat.hp > 0)
			{
				printf("\n\nWait, what?! He can also use potions?! He just healed... You will need to weaken him again! There is no other way!");
				getchar();
				wrath->items.potions -= 1;
				hero->items.potions += 1;
				wrath->combat.hp += 50;
				if (wrath->combat.hp > hero->full_hp)
				{
					wrath->combat.hp = hero->full_hp;
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
				int crit_chance = rand() % 6; // Critical hit
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
				printf("\n\nHe swung his sword towards you! He dealt %i damage to you! %i HP left", damage_to_hero, hero->combat.hp);
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