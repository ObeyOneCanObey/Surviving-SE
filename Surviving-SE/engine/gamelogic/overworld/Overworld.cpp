#include "Overworld.h"

void Overworld::initMap() {
  doMovement(NOMOVEMENT, &currentPlayerPos, &gridCoords, mapGrid, &monsterEncounter);
}

void Overworld::updateMap(enum movementOption move) {
  doMovement(move, &currentPlayerPos, &gridCoords, mapGrid, &monsterEncounter);
}

bool Overworld::isMonsterFight() {
  if (enterFight(currentPlayerPos.xpos, currentPlayerPos.ypos, mapGrid, &monsterEncounter)) {
    numEncounters++;
    return true;
  }
  return false;
}

bool Overworld::isBossFight() {
  if (numEncounters > 2) {
    
    numEncounters = 0;
    return true;
  }
  return false;
}

int* Overworld::getMap() {
  return mapGrid;
}

struct position Overworld::getGridCoords() {
  return gridCoords;
}

void Overworld::printMap() {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      std::cout << mapGrid[i * MAP_WIDTH + j];
    }
  }
}

struct position Overworld::getPlayerPos() {
  return currentPlayerPos;
}

int Overworld::getMonsterEncounter() {
  return monsterEncounter;
}

int Overworld::getNumMonsterEncounters() {
  return numEncounters;
}

void Overworld::resetOverworld() {
  currentPlayerPos = { INITIALPLAYERXPOS, INITIALPLAYERYPOS };
  gridCoords = { INITIALGRIDXPOS, INITIALGRIDYPOS };
  initMap();
  resetMonsterGrid();
  for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
    mapGrid[i] = 0;
  }
}
