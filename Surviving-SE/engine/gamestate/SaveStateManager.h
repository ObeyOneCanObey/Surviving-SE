#ifndef SAVESTATEMANAGER_H
#define SAVESTATEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>

#include <string.h>


class SaveStateManager {
public:
  void recordSaveData(int level, int playerX, int playerY, int health, int gridX, int gridY, int numMonsterEncounters);
  void deleteSaveData();
  void loadSaveData(int *level, int *playerX, int *playerY, int *health, int *gridX, int *gridY, int *numMonsterEncounters);
};

#endif
