#include "MonsterFight.h"

void MonsterFight::setFightHealths(int playerHealth) {
  this->playerHealth = playerHealth;
  monsterHealth = currentMonster.health;
}

void MonsterFight::updateCurrentLevel(int newLevel) {
  currentLevel = newLevel;
  setCurrentLevel(currentLevel);
}

void MonsterFight::updateCurrentMonster(int monsterEncounter, bool isBossFight) {
  currentMonster = getMonster(monsterEncounter, isBossFight);
}

void MonsterFight::updateHealth(bool usedWeapon, int moveChoice) {
  if (usedWeapon) {
    PlayerTurnFight(moveChoice, &monsterHealth);
  } else {
    playerTurnHeal(potionValues[moveChoice], &playerHealth);
    potions.erase(find(potions.begin(), potions.end(), potionValues[moveChoice]));
  }
  monsterTurnFight(&playerHealth, &currentMonster);
}

int MonsterFight::getPlayerHealth() {
  return playerHealth;
}

int MonsterFight::getMonsterHealth() {
  return monsterHealth;
}

void MonsterFight::generatePotion() {
  potions.push_back(RandomPotionGenerator());
}

int MonsterFight::getPotionCount(int value) {
  return std::count(potions.begin(), potions.end(), value);
}

void MonsterFight::deletePotions() {
  potions.clear();
}
