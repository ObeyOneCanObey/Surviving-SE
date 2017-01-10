#ifndef VICTORYSTATE_H
#define VICTORYSTATE_H

#include "GameState.h"

class VictoryState : public GameState {
public:
  void init(Window window);
  void updateState(enum Input input, GameStateManager *gameStateManager);
  void renderState(Window window);
  void deleteSave();
private:
  Sprite victory;
  Sprite arrow;
};

#endif
