#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

class MainMenuState : public GameState {
public:
  void init(Window window);
  void updateState(enum Input input, GameStateManager *gameStateManager);
  void renderState(Window window);
  void deleteSaveData();
  void loadSaveData();
private:
  Sprite arrow;
  Sprite title;
  bool isOnNewGameButton = true;
};

#endif
