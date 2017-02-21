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

	hero_data hero;

	for (int i = 0; i <= my_strlen(hero_name); i++)
	{
		hero.name[i]			= hero_name[i];
	}
	hero.combat.hp				= 200;
	hero.full_hp				= 200;
	hero.combat.attack_min		= 10;
	hero.combat.attack_max		= 25;
	hero.combat.armor			= 5;
	hero.combat.mana			= 100;
	hero.coins					= 100;
	hero.xp						= 0;
	hero.items.potions			= 1;
	hero.level					= 1;
	hero.spells.yol_toor_shul	= 1;
	hero.spells.synthesis		= 1;
	hero.spells.icicle_fall		= 1;
	hero.spells.windstrike		= 1;
	hero.AoE					= 0;
	hero.pasive					= 0;

	// Stats check and start of the adventure
	printf("\n\nThis are the stats. At the moment you have %i health points(HP), %i minimum attack, %i maximum attack and %i of armor. You also have %i coins and %i health potions(each heals 50HP).", hero.combat.hp, hero.combat.attack_min, hero.combat.attack_max, hero.combat.armor, hero.coins, hero.items.potions);
	getchar();
	printf("\n\nIt is time to commence your adventure, %s. Welcome to the dungeon...", hero.name);
	getchar();

	monster_data goblins[6], globin, wrath;

	int wave_number = 1;

	int damage_to_enemy;

	while (hero.combat.hp > 0)
	{
		if (wave_number == 5) // Midboss fight function
		{
			midboss_fight(&hero, &globin, &goblins[0], &goblins[1]);
			if (hero.combat.hp <= 0)
			{
				break;
			}
			else
			{
				printf("\n\nYou have fought well %s. Now Let me reward you with a full healing of your wounds and calming your mind.", hero.name);
				getchar();
				hero.combat.hp = hero.full_hp;
				wave_number++;
			}
		}

		if (wave_number > 1) // Prewave shop
		{
			pre_wave_shop(&hero, wave_number);
		}

		if (wave_number == 10) // Final boss fight function
		{
			final_boss_fight(&hero, &wrath);
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
		int wave_size = rand() % 6 + 1;

		printf("\n\nBe careful! You are being attack by the wave %i of goblins! #%i now in front of you! Attack!", wave_number, wave_size);
		getchar();

		for (int i = 0; i < wave_size; i++) // Generation of goblin stats
		{
			gob_stats(&goblins[i], &hero);
		}

		int goblins_alive = wave_size;

		while (goblins_alive > 0 && wave_number <= 10)
		{
			goblins_alive = wave_size;

			if (hero.combat.hp > 0) // Hero attacks
			{
				int goblin_attacked_index = rand() % wave_size;

				if (goblins[goblin_attacked_index].combat.hp > 0)
				{									
					damage_to_enemy = hero_attacking_calculations(&hero, &goblins[goblin_attacked_index]);

					if (hero.AoE == 0 && hero.pasive == 0)
					{
						printf("\n\nYou are hitting the goblin #%i.", goblin_attacked_index + 1);
						getchar();

						if (damage_to_enemy > 0)
						{
							goblins[goblin_attacked_index].combat.hp -= damage_to_enemy;
							printf("\n\nWell done %s! You got him well! His life was recuced by %i!", hero.name, damage_to_enemy);
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
					}
					else if (hero.AoE == 1)
					{
						printf("\n\nAll enemies' HP recuced by %i!", damage_to_enemy);
						getchar();

						for (int i = 0; i < wave_size; i++)
						{
							goblins[i].combat.hp -= (damage_to_enemy - goblins[i].combat.armor);
							if (goblins[i].combat.hp <= 0)
							{
								hero.coins += goblins[i].coins;
								hero.xp += goblins[i].xp;
								hero.items.potions += goblins[i].items.potions;

								printf("\n\nYou killed the goblin %i! You recieved %i points of experience and %i coins, but keep your guard up, there may be more of them.", i + 1, goblins[i].xp, goblins[i].coins);
								getchar();

								if (goblins[i].items.potions == 1)
								{
									printf("\n\nOh? What is this? Seems like that goblin had a potion with him. Now you have %i potions", hero.items.potions);
									getchar();
								}
							}
						}
						hero.AoE = 0;
					}
					else
					{
						hero.pasive = 0;
					}

					reberu_appu(&hero); // Level up

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

					for (int i = 0; i < wave_size; i++) // Goblins attack
					{
						if (hero.combat.hp > 0)
						{
							if (goblins[i].combat.hp > 0)
							{
								int attack_of_goblin = goblins[i].combat.attack_min + rand() % (goblins[i].combat.attack_max - goblins[i].combat.attack_min);
								int damage_hero_recieves = attack_of_goblin - hero.combat.armor;

								if (damage_hero_recieves > 0)
								{
									int crit_chance = rand() % 6; // Critical hit
									if (crit_chance == 5)
									{
										damage_hero_recieves *= 2;
										printf("\n\nOh no! He is aiming at a weak point! This is going to hurt the double...");
										getchar();
									}

									hero.combat.hp -= damage_hero_recieves;

									if (hero.combat.hp < 0)
									{
										hero.combat.hp = 0;
									}

									printf("\n\nGoblin #%i hits you for %i! You have %i HP remaining!", i + 1, damage_hero_recieves, hero.combat.hp);
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