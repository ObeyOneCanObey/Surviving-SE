#include "VictoryState.h"

void VictoryState::init(Window window) {
  renderer.init(window.getWidth(), window.getHeight());
  renderer.setClearColour(WHITE);
  
  victory.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "you_win.png");
  victory.changeLocation(0.0f, 120.0f);
  victory.changeScale(18.0f, 5.0f);

  arrow.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "arrow.png");
  arrow.changeLocation(75.0f, -99.0f);
}

void VictoryState::updateState(enum Input input, GameStateManager *gameStateManager) {
  if (input == MENUSELECT) {
    gameStateManager->getSaveStateManager()->deleteSaveData();
    gameStateManager->enterNewState(stateMainMenu);
  }
}

void VictoryState::renderState(Window window) {
  renderer.clear();
  
  renderer.getFontRedererer()->renderText("Congratulations, you've survived your 1A term!", -220.0f, 0.0f, 0.5f, SE_PURPLE);
  renderer.getFontRedererer()->renderText("Be proud of your accomplishments. Only 4.5 years to go!", -265.0f, -20.0f, 0.5f, SE_PURPLE);
  renderer.getFontRedererer()->renderText("Main Menu", -140.0f, -110.0f, 1.0f, SE_PURPLE);
  
  renderer.getSpriteRenderer()->render(victory);
  renderer.getSpriteRenderer()->render(arrow);
  
  renderer.render(window);
}
