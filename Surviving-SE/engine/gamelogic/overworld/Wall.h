#ifndef WALL_H
#define WALL_H

#include <stdlib.h>
#include <stdbool.h>

#include "OverworldProperties.h"

#define WALL 9

//Returns true if the position that sprite wants to move to does not have a wall
bool NoWall(int xPos, int yPos, int Grid[], enum movementOption move);

void buildWall(int xCoord, int yCoord);
void updateWall(int xCoord, int yCoord, int Grid[]);

#endif
