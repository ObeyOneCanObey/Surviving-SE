#ifndef MONSTER_H
#define MONSTER_H

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "OverworldProperties.h"
#include "Wall.h"

#define NUM_MAX_MONSTERS 4
#define MONSTER_RANGE 5

void ifAttackOccurs(int Grid[]);

//Generates monster and places it on the grid
void monsterGenerator(int Grid[]);

//Returns true if a monster is generated
bool RandomMonsterGenerator();

//Monster follows player if within range
void monsterFollow(int playerX, int playerY, int Grid[], int *monsterEncounter);

//Updates monster coordinates
void monsterUpdate(int playerX, int playerY, int Grid[], int *monsterEncounter);

//Returns true if player and monster are on same part of grid
bool enterFight(int playerX, int playerY, int Grid[], int *monsterEncounter);

void resetMonsterGrid();

#endif
