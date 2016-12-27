#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include "creatures.h"
#include "Mystrings.h"
#include "Extras.h"

int check_get_character_within_range(int num_checked, int max_range, int min_range)
{
	if (num_checked <= max_range && num_checked >= min_range)
	{
		return num_checked;
	}
	else if (num_checked < min_range)
	{
		return min_range;
	}
	else
	{
		return max_range;
	}
}

void main()
{

	//	Input user. hero name , hp, etc
	char hero_name[10];
	printf("Enter the name of your hero: ");
	scanf("%s", &hero_name);
	capitalize(hero_name);

	int hero_hp			= 1;
	int max_hp			= 200;
	int min_hp			= 50;
	int hero_dmg_min	= 1;
	int hero_dmg_max	= 1;
	int max_dmg			= 25;
	int hero_armor		= 1;

	printf("\n\nEnter combat stats for %s: ", hero_name);
	printf("\n\nFirst you should enter the number of life points you are disposed to have. Take into account that no one can spend less than 50 life point and the maximum is 200 for trial.\n\n");
	scanf("%i", &hero_hp);
	hero_hp = check_get_character_within_range(hero_hp, max_hp, min_hp);
	printf("\n\nNow is time for you to decide your own power. As an imperfect creature, you are unable to decide with precision and there are some limits to your power. So, here! Which will be the minimum of your power? It must remain within 0 and 10, no more no less. And the maximum? Of course it will be bigger than the minimum right? Remember that your limit is 25.\n\nMinimum: ");
	scanf("%i", &hero_dmg_min);
	hero_dmg_min = check_get_character_within_range(hero_dmg_min, 10, 1);
	printf("\n\nMaximum: ");
	scanf("%i", &hero_dmg_max);
	hero_dmg_max = check_get_character_within_range(hero_dmg_max, max_dmg, (hero_dmg_min + 1));
	printf("\n\nDo you need armor? In that case keep in mind your limit is 5, more would be too much weight.\n\n");
	scanf("%i", &hero_armor);
	hero_armor = check_get_character_within_range(hero_armor, 5, 0);

	hero_data hero;

	for (int i = 0; i <= my_strlen(hero_name); i++)
	{
		hero.name[i]			= hero_name[i];
	}
	hero.combat.hp				= hero_hp;
	hero.combat.attack_min		= hero_dmg_min;
	hero.combat.attack_max		= hero_dmg_max;
	hero.combat.armor			= hero_armor;
	hero.coins					= 100;
	hero.xp						= 0;
	hero.items.potions			= 1;

	// Stats check and start of the adventure
	printf("\n\nSo this are the stats you chose? At the moment you have %i health points(HP), %i minimum attack, %i maximum attack and %i of armor. You also have %i coins and %i health potions(each heals 50HP).", hero.combat.hp, hero.combat.attack_min, hero.combat.attack_max, hero.combat.armor, hero.coins, hero.items.potions);
	getchar();
	printf("\n\nIt is time to commence your adventure, %s. Welcome to the dungeon...", hero.name);
	getchar();

	monster_data goblins[6], globin, wrath;

	int wave_number = 1;

	int full_hero_hp = hero.combat.hp;

	while (hero.combat.hp > 0)
	{
		if (hero.combat.hp < full_hero_hp) // Heal and shop function
		{
			pre_wave_shop(&hero, full_hero_hp, wave_number);
		}

		if (wave_number == 5) // Midboss fight function
		{
			midboss_fight(&hero, &globin, &goblins[0], &goblins[1]);
			if (hero.combat.hp <= 0)
			{
				break;
			}
			else
			{
				printf("\n\nYou have fought well %s. Now Let me reward you with a full healing of your wounds.", hero.name);
				getchar();
				hero.combat.hp = full_hero_hp;
				wave_number++;
			}

		}

		if (wave_number == 10) // Final boss fight function
		{
			final_boss_fight(&hero, &wrath, full_hero_hp);
			if (hero.combat.hp <= 0)
			{
				break;
			}
			else
			{
				printf("\n\nY-you did it...? You won? I cannot believe it... You really won... Thank you... *sob* Thank you very much %s", hero.name);
				getchar();
				break;
			}
		}

		srand(time(NULL));

		int wave_size = rand() % 1 + 1;

		printf("\n\nBe careful! You are being attack by the wave %i of goblins! #%i now in front of you! Attack!", wave_number, wave_size);
		getchar();

		for (int i = 0; i < wave_size; i++) // Generation of goblin stats
		{
			goblins[i].combat.hp				= 1 + rand() % 24;
			goblins[i].combat.armor				= rand() % 4;
			goblins[i].combat.attack_min		= rand() % 7;
			goblins[i].combat.attack_max		= goblins[i].combat.attack_min + 5 + rand() % 7;
			goblins[i].coins					= rand() % 20;
			goblins[i].xp						= 15;
			int potion_possibility				= rand() % 100 + 1;
			if (potion_possibility < 11)
			{
				goblins[i].items.potions		= 1;
			}
			else
			{
				goblins[i].items.potions		= 0;
			}
		}

		int goblins_alive = wave_size;

		while (goblins_alive > 0 && wave_number <= 10)
		{
			goblins_alive = wave_size;

			if (hero.combat.hp > 0) // Hero attacks
			{
				int goblin_attacked_index = rand() % wave_size;
				srand(time(NULL));

				if (goblins[goblin_attacked_index].combat.hp > 0)
				{
					int total_hero_attack = hero.combat.attack_min + rand() % hero.combat.attack_max;
					int damage_to_goblin = total_hero_attack - goblins[goblin_attacked_index].combat.armor;
				
					printf("\n\nYou are hitting the goblin #%i.", goblin_attacked_index + 1);
					getchar();

					if (damage_to_goblin > 0)
					{
						int crit_chance = rand() % 6;
						if (crit_chance == 5)
						{
							damage_to_goblin *= 2;
							printf("\n\nCritical hit!");
							getchar();
						}

						goblins[goblin_attacked_index].combat.hp -= damage_to_goblin;
						printf("\n\nWell done %s! You got him well! His life was recuced by %i!", hero.name, damage_to_goblin);
						getchar();

						if (goblins[goblin_attacked_index].combat.hp <= 0)
						{
							hero.coins += goblins[goblin_attacked_index].coins;
							hero.xp += goblins[goblin_attacked_index].xp;
							hero.items.potions += goblins[goblin_attacked_index].items.potions;

							printf("\n\nYou killed it! You recieved %i points of experience and %i coins, but keep your guard up, there may be more of them.", goblins[goblin_attacked_index].xp, goblins[goblin_attacked_index].coins);
							getchar();

							if (goblins[goblin_attacked_index].items.potions == 1)
							{
								printf("\n\nOh? What is this? Seems like that goblin had a potion with him. Now you have %i potions", hero.items.potions);
								getchar();
							}
						}
					}
					else
					{
						printf("\n\nYou need to try harder! Those guys will not recieve damage from that.");
						getchar();
					}

					for (int i = 0; i < wave_size; i++)
					{
						if (goblins[i].combat.hp <= 0)
						{
							goblins_alive--;
						}
					}
					if (goblins_alive > 0)
					{
						printf("\n\nDo not lower your ward! You are being attacked!");
						getchar();
					}

					for (int i = 0; i <= wave_size; i++) // Goblins attack
					{
						if (hero.combat.hp > 0)
						{
							if (goblins[i].combat.hp > 0)
							{
								int attack_of_goblin = goblins[i].combat.attack_min + rand() % (goblins[i].combat.attack_max - goblins[i].combat.attack_min);
								int damage_hero_recieves = attack_of_goblin - hero.combat.armor;

								if (damage_hero_recieves > 0)
								{
									int crit_chance = rand() % 6;
									if (crit_chance == 5)
									{
										damage_hero_recieves *= 2;
										printf("Oh no! He is aiming at a weak point! This is going to hurt the double...");
										getchar();
									}

									hero.combat.hp -= damage_hero_recieves;
									if (hero.combat.hp < 0)
									{
										hero.combat.hp = 0;
									}
									printf("\n\nGoblin #%i hits you for %i! You have %i HP remaining! Be careful of the rest!", i + 1, damage_hero_recieves, hero.combat.hp);
									getchar();
								}
								else
								{
									printf("\n\nGood job %s. You blocked the goblin #%i attack perfectly. But there are more!", hero.name, i + 1);
									getchar();
								}
							}
						}
					}
				}
			}
			else
			{
				break;
			}
		}
		wave_number++;
	}

	if (hero.combat.hp <= 0) // Ded
	{
		printf("\n\n%s? Are you ok? Hey! Can you hear me?! %s?! NOOOOOOO!!", hero.name, hero.name);
		getchar();
	}
}