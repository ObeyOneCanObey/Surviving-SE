#ifndef DEFEATSTATE_H
#define DEFEATSTATE_H

#include "GameState.h"

class DefeatState : public GameState {
public:
  void init(Window window);
  void updateState(enum Input input, GameStateManager *gameStateManager);
  void renderState(Window window);
  void deleteSave();
private:
  Sprite defeat;
  Sprite arrow;
};


#endif
