#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>

#include "../glutils/Window.h"

#include "gamestate/GameStateManager.h"
#include "GameInput.h"

class GameEngine {
public:
  void init();
  void getInput(enum Input inputValue);
  void update();
  void render();
  void cleanup();
  bool isExitedGame();
  Window getWindowObject();
  GameStateManager getGameStateManager();
private:
  Window window;
  enum Input inputValue;
  GameStateManager gameStateManager;
};

#endif
