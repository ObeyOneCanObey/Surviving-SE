#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <iostream>

#include "GameState.h"
#include "MainMenuState.h"
#include "OverworldState.h"
#include "InGameMenuState.h"
#include "FightState.h"
#include "VictoryState.h"
#include "DefeatState.h"
#include "CutSceneState.h"
 
#include "../GameInput.h"

#include "SaveStateManager.h"

class GameStateManager {
public:
  GameStateManager();
  void init(Window window);
  GameState* getCurrentState();
  void enterNewState(enum gameState);
  void cleanup();
  void updateGameStateParams(int level, int monsterEncounter, int numMonsterEncounters, bool isNewLevel, int health, bool isFight, bool isMonsterFight);
  void updateLocationParams(int playerX, int playerY, int gridX, int gridY);
  void updateBossFightParams(bool isBossFight, bool isBeatenBoss);
  int getMonsterEncounter();
  void recordSaveData();
  void deleteSaveData();
  SaveStateManager* getSaveStateManager();
  
  //Getters for global game state params
  //Used for save recording and loading save state info
  int* getPlayerX();
  int* getPlayerY();
  int* getGridX();
  int* getGridY();
  int* getHealth();
  int* getNumEncounters();
  int* getLevel();
  
private:
  SaveStateManager saveStateManager;
  
  GameState *mainMenu;
  GameState *overworld;
  GameState *inGameMenu;
  GameState *fight;
  GameState *victory;
  GameState *defeat;
  GameState *cutScene;
  GameState *currentGameState;
  enum gameState currentStateEntered;
  
  int level = 0;
  int monsterEncounter;
  bool isBossFight = false;
  bool isNewLevel = false;
  int numMonsterEncounters = 0;
  int health;
  bool isBeatenBoss;
  bool isFight;
  bool isMonsterFight;
  int playerX;
  int playerY;
  int gridX;
  int gridY;
};

#endif
