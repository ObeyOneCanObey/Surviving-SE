#ifndef OVERWORLDSTATE_H
#define OVERWORLDSTATE_H

#define MOVE_TO_ORIGIN -400 + 32 / 2, 300 - 32 / 2
#define GRID_WIDTH 800 / MAP_WIDTH
#define GRID_HEIGHT -600 / MAP_HEIGHT

#include <stdlib.h>

#include "GameState.h"
#include "../gamelogic/overworld/Overworld.h"
#include "../gamelogic/overworld/OverworldProperties.h"

class OverworldState : public GameState {
public:
  void init(Window window);
  void updateState(enum Input input, GameStateManager *gameStateManager);
  void renderState(Window window);
  void updateMapContents();
  void updatePlayerPos();
  void updateGameStateParams(GameStateManager *gameStateManager, int monsterEncounter, int level, int numMonsterEncounters, bool isNewLevel, bool isFight, bool isMonsterFight);
  void updateBossParams(GameStateManager *gameStateManager, bool isBossFight);
  
private:
  Overworld overworld;
  Sprite playerAvater;
  Sprite wall;
  Sprite seMonster;
  Sprite csMonster;
  Sprite mathMonster;
  Sprite eceMonster;
  int overworldMap[MAP_WIDTH * MAP_HEIGHT];
  struct position currentPlayerPos;
  struct position currentGridPos;
};

#endif
