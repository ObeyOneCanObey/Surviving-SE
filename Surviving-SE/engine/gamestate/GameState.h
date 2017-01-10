#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../../glutils/Renderer.h"
#include "../GameInput.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#define SE_PURPLE glm::vec3(93.0f / 255.0f, 14.0f / 255.0f, 129.0f / 255.0f)
#define WHITE glm::vec3(1.0f, 1.0f, 1.0f)
#define BLACK glm::vec3(0.0f, 0.0f, 0.0f)
#define LIGHT_GREY glm::vec3(153.0f / 255.0f, 153.0f / 255.0f, 153.0f / 255.0f)

class GameStateManager;

enum gameState {
  stateMainMenu = 0,
  stateOverworld = 1,
  stateInGameMenu = 2,
  stateFight = 3,
  stateVictory = 4,
  stateDefeat = 5,
  stateCutScene = 6
};

//Abstract class that other game states inherit from
class GameState {
public:
  virtual void init(Window window) = 0;
  virtual void updateState(enum Input input, GameStateManager *gameStateManager) = 0;
  virtual void renderState(Window window) = 0;
  Renderer* getRenderer() { return &renderer; };
  void updateGameGlobalVariables(int newLevel, int newMonsterEncounter, bool isBossFight, bool isNewLevel, int numMonsterEncounters, int health, bool isBeatenBoss, bool isFight, bool isMonsterFight, int playerX, int playerY, int gridX, int gridY) {
    level = newLevel;
    monsterEncounter = newMonsterEncounter;
    this->isBossFight = isBossFight;
    this->isNewLevel = isNewLevel;
    this->numMonsterEncounters = numMonsterEncounters;
    this->health = health;
    this->isBeatenBoss = isBeatenBoss;
    this->isFight = isFight;
    this->isMonsterFight = isMonsterFight;
    this->playerX = playerX;
    this->playerY = playerY;
    this->gridX = gridX;
    this->gridY = gridY;
  };
protected:
  Renderer renderer;
  int level;
  int monsterEncounter;
  bool isFight;
  bool isMonsterFight;
  bool isBossFight;
  bool isBeatenBoss;
  bool isNewLevel;
  int numMonsterEncounters;
  int health;
  int playerX;
  int playerY;
  int gridX;
  int gridY;
};

//include needed here to define forward declaration
//would not compile otherwise since GameStateManager object is incomplete type
//GameStateManager also contains pointers to GameState objects, so need this work around
#include "GameStateManager.h"

#endif
