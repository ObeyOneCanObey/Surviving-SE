#include "FightSimulator.h"

struct weapon AllWeapons[4][3] = {
  {{6 , 8} , {8 , 10} , {10 , 12}} ,
  {{10 , 12} , {12 , 14} , {16 , 18}} ,
  {{18 , 20} , {20 , 22} , {22 , 24}} ,
  {{24 , 26} , {26 , 28} , {28 , 30}}
};

struct monster AllMonsters[4][3] = {
  { {5, 10} , {5, 10} , {5 ,10} },
  { {5,10} , {10,20} , {15,30} },
  { {10,10} , {15,20} , {20,30} },
  { {15,10} , {20,20} , {25,30} },
};

struct monster AllBosses[4] = { {15, 40} , {20 , 50} , {25 , 60} , {35, 70} };

int currentLevel = 0;

// returns values of 25, 35, and 45
int RandomPotionGenerator(){
  int ctr  = 1;
  int n =  1 + (rand()%13);
  if(n > 6){n = n - 6;}
  while(n > ctr*(ctr+1)/2){ctr+=1;}
  return 10*(n - ctr*(ctr-1)/2)+15;
}

struct monster getMonster(int monsterEnounter, bool isBossFight) {
  if (isBossFight)
     return AllBosses[currentLevel];
  else
    return AllMonsters[currentLevel][monsterEnounter];
}

void setCurrentLevel(int level) {
  currentLevel = level;
}

void PlayerTurnFight(int weaponChoice, int *currentMonsterHealth) {
  struct weapon currentWeapon = AllWeapons[currentLevel][weaponChoice];
  if (rand() % 4 != 0) {
    *currentMonsterHealth -= (rand() % (currentWeapon.maxDamage - currentWeapon.minDamage) + currentWeapon.minDamage);
    if (*currentMonsterHealth < 0)
      *currentMonsterHealth = 0;
  }
}

void playerTurnHeal(int potionHealValue, int *currentPlayerHealth) {
  *currentPlayerHealth += potionHealValue;
  if (*currentPlayerHealth > 100)
    *currentPlayerHealth = 100;
}

void monsterTurnFight(int *currentPlayerHealth, struct monster *currentMonster) {
  if (rand() % 3 != 0) {
    *currentPlayerHealth -= (currentMonster->MinDamage + rand() % 5);
    if (*currentPlayerHealth < 0)
      *currentPlayerHealth = 0;
  }
}
