#ifndef MONSTERFIGHT_H
#define MONSTERFIGHT_H

#include <vector>
#include <algorithm>

extern "C" {
  #include "FightSimulator.h"
}

class MonsterFight {
public:
  void updateCurrentLevel(int newLevel);
  void updateHealth(bool usedWeapon, int moveChoice);
  void updateCurrentMonster(int monsterEncounter, bool isBossFight);
  int getPlayerHealth();
  int getMonsterHealth();
  void generatePotion();
  void setFightHealths(int playerHealth);
  int getPotionCount(int value);
  void deletePotions();
  
private:
  int playerHealth;
  int monsterHealth;
  int currentLevel;
  struct monster currentMonster;
  std::vector<int> potions;
  int potionValues[3] = {25, 35, 45};
};

#endif
