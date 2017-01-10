#ifndef FIGHTSIMULATOR_H
#define FIGHTSIMULATOR_H

#include <stdlib.h>
#include <stdbool.h>

struct monster {
  int MinDamage;
  int health;
};

struct weapon {
  int minDamage;
  int maxDamage;
};

struct monster getMonster(int monsterEncounter, bool isBossFight);
int RandomPotionGenerator();
void setCurrentLevel(int level);
//Updates monster health after player attacks monster
void PlayerTurnFight(int weapon, int *currentMonsterHealth);
//Updates player health after player heals
void playerTurnHeal(int potion, int *currentPlayerHealth);
//Updates player health after monster attacks player
void monsterTurnFight(int *currentPlayerHealth, struct monster *currentMonster);

#endif
