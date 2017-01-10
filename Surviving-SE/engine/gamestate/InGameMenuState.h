#ifndef INGAMEMENU_H
#define INGAMEMENU_H

#include "GameState.h"

class InGameMenuState : public GameState {
public:
  void init(Window window);
  void updateState(enum Input input, GameStateManager *gameStateManager);
  void renderState(Window window);
private:
  Sprite menuBorder;
  Sprite arrow;
  bool returnToMenu = false;
};

#endif
