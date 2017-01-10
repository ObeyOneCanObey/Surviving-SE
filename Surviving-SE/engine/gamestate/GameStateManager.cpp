#include "GameStateManager.h"

GameStateManager::GameStateManager() {
  mainMenu = new MainMenuState();
  overworld = new OverworldState();
  inGameMenu = new InGameMenuState();
  fight = new FightState();
  victory = new VictoryState();
  defeat = new DefeatState();
  cutScene = new CutSceneState();
  currentGameState = mainMenu;
}

void GameStateManager::init(Window window) {
  mainMenu->init(window);
  overworld->init(window);
  inGameMenu->init(window);
  fight->init(window);
  fight->updateGameGlobalVariables(level, monsterEncounter, isBossFight, numMonsterEncounters, isNewLevel, health, isBeatenBoss, isFight, isMonsterFight, playerX, playerY ,gridX, gridY);
  victory->init(window);
  defeat->init(window);
  cutScene->init(window);
}

GameState* GameStateManager::getCurrentState() {
  return currentGameState;
}

void GameStateManager::enterNewState(enum gameState gameState) {
  switch (gameState) {
    case stateMainMenu:
      mainMenu->updateGameGlobalVariables(level, monsterEncounter, isBossFight, isNewLevel, numMonsterEncounters, health, isBeatenBoss, isFight, isMonsterFight, playerX, playerY ,gridX, gridY);
      currentStateEntered = stateMainMenu;
      currentGameState = mainMenu;
      break;
    case stateOverworld:
      overworld->updateGameGlobalVariables(level, monsterEncounter, isBossFight, isNewLevel, numMonsterEncounters, health, isBeatenBoss, isFight, isMonsterFight, playerX, playerY ,gridX, gridY);
      currentStateEntered = stateOverworld;
      currentGameState = overworld;
      break;
    case stateInGameMenu:
      inGameMenu->updateGameGlobalVariables(level, monsterEncounter, isBossFight, isNewLevel, numMonsterEncounters, health, isBeatenBoss, isFight, isMonsterFight, playerX, playerY ,gridX, gridY);
      currentStateEntered = stateInGameMenu;
      currentGameState = inGameMenu;
      break;
    case stateFight:
      fight->updateGameGlobalVariables(level, monsterEncounter, isBossFight, isNewLevel, numMonsterEncounters, health, isBeatenBoss, isFight, isMonsterFight, playerX, playerY ,gridX, gridY);
      currentStateEntered = stateFight;
      currentGameState = fight;
      break;
    case stateVictory:
      victory->updateGameGlobalVariables(level, monsterEncounter, isBossFight, isNewLevel, numMonsterEncounters, health, isBeatenBoss, isFight, isMonsterFight, playerX, playerY ,gridX, gridY);
      currentStateEntered = stateVictory;
      currentGameState = victory;
      break;
    case stateDefeat:
      defeat->updateGameGlobalVariables(level, monsterEncounter, isBossFight, isNewLevel, numMonsterEncounters, health, isBeatenBoss, isFight, isMonsterFight, playerX, playerY ,gridX, gridY);
      currentStateEntered = stateDefeat;
      currentGameState = defeat;
      break;
    case stateCutScene:
      cutScene->updateGameGlobalVariables(level, monsterEncounter, isBossFight, isNewLevel, numMonsterEncounters, health, isBeatenBoss, isFight, isMonsterFight, playerX, playerY ,gridX, gridY);
      currentStateEntered = stateCutScene;
      currentGameState = cutScene;
      break;
    default:
      std::cout << "ERROR::GAMESTATEMANAGER: Invalid game state" << std::endl;
      break;
  }
}

void GameStateManager::cleanup() {
  
}

int* GameStateManager::getPlayerX() {
  return &playerX;
}

int* GameStateManager::getPlayerY() {
  return &playerY;
}

int* GameStateManager::getGridX() {
  return &gridX;
}

int* GameStateManager::getGridY() {
  return &gridY;
}

int* GameStateManager::getHealth() {
  return &health;
}

int* GameStateManager::getNumEncounters() {
  return &numMonsterEncounters;
}

int* GameStateManager::getLevel() {
  return &level;
}

void GameStateManager::updateGameStateParams(int level, int monsterEncounter, int numMonsterEncounters, bool isNewLevel, int health, bool isFight, bool isMonsterFight) {
  this->level = level;
  this->monsterEncounter = monsterEncounter;
  this->numMonsterEncounters = numMonsterEncounters;
  this->isNewLevel = isNewLevel;
  this->health = health;
  this->isFight = isFight;
  this->isMonsterFight = isMonsterFight;
}

void GameStateManager::updateBossFightParams(bool isBossFight, bool isBeatenBoss) {
  this->isBossFight = isBossFight;
  this->isBeatenBoss = isBeatenBoss;
}

void GameStateManager::updateLocationParams(int playerX, int playerY, int gridX, int gridY) {
  this->playerX = playerX;
  this->playerY = playerY;
  this->gridX = gridX;
  this->gridY = gridY;
}

void GameStateManager::recordSaveData() {
  saveStateManager.recordSaveData(level, playerX, playerY, health, gridX, gridY, numMonsterEncounters);
}

void GameStateManager::deleteSaveData() {
  saveStateManager.loadSaveData(&level, &playerX, &playerY, &health, &gridX, &gridY, &numMonsterEncounters);
}

SaveStateManager* GameStateManager::getSaveStateManager() {
  return &saveStateManager;
}
