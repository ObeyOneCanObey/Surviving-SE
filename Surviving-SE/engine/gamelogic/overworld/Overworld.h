#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <stdlib.h>

#include "OverworldProperties.h"

#include <iostream>
#include <string>

extern "C"
{
  #include "Wall.h"
  #include "Player.h"
  #include "Monster.h"
}

class Overworld {
  public:
  void initMap();
  void updateMap(enum movementOption move);
  bool isMonsterFight();
  bool isBossFight();
  void printMap();
  int* getMap();
  struct position getPlayerPos();
  //Returns value of monster so monster of various difficulty can be generated
  int getMonsterEncounter();
  int getNumMonsterEncounters();
  void resetOverworld();
  struct position getGridCoords();
  
  private:
  int mapGrid[MAP_WIDTH * MAP_HEIGHT] = { 0 };
  struct position currentPlayerPos = { INITIALPLAYERXPOS, INITIALPLAYERYPOS };
  struct position gridCoords = { INITIALGRIDXPOS, INITIALGRIDYPOS };
  int monsterEncounter;
  int numEncounters = 0;
};

#endif
