#ifndef PLAYER_H
#define PLAYER_H

#define X_LEFT_BOUND -1
#define X_RIGHT_BOUND 25
#define Y_LOWER_BOUND -1
#define Y_UPPER_BOUND 25

#define PLAYER 5

#include <stdlib.h>
#include <math.h>
#include "stdio.h"

#include "OverworldProperties.h"
#include "Wall.h"
#include "Monster.h"

//Moves player in the overworld and updates positions on the grid of monsters and walls accordingly
void doMovement(enum movementOption move, struct position *currentPlayerPosition, struct position *gridCoords, int Grid[], int *monsterEncounters);

//Regenerate map if player moves past bounds of grid
void generateNewMapContents(int xPos, int yPos, int Grid[], int *monsterEncounters);

#endif
