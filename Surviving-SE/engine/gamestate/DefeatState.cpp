#include "DefeatState.h"

void DefeatState::init(Window window) {
  renderer.init(window.getWidth(), window.getHeight());
  renderer.setClearColour(BLACK);
  
  defeat.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "game_over.png");
  defeat.changeLocation(0.0f, 120.0f);
  defeat.changeScale(18.0f, 5.0f);
  
  arrow.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "arrow.png");
  arrow.changeLocation(75.0f, -99.0f);
}

void DefeatState::updateState(enum Input input, GameStateManager *gameStateManager) {
  if (input == MENUSELECT) {
    gameStateManager->getSaveStateManager()->deleteSaveData();
    gameStateManager->enterNewState(stateMainMenu);
  }
}

void DefeatState::renderState(Window window) {
  renderer.clear();
  
  renderer.getFontRedererer()->renderText("Not everything worked out nicely, but don’t give up.", -240.0f, 20.0f, 0.5f, SE_PURPLE);
  renderer.getFontRedererer()->renderText("There will be other chances.", -140.0f, 0.0f, 0.5f, SE_PURPLE);
  renderer.getFontRedererer()->renderText("You were still accepted because we thought you could do well here.", -310.0f, -20.0f, 0.5f, SE_PURPLE);
  renderer.getFontRedererer()->renderText("None of that has changed.", -125.0f, -40.0f, 0.5f, SE_PURPLE);
  
  renderer.getFontRedererer()->renderText("Main Menu", -140.0f, -110.0f, 1.0f, SE_PURPLE);
  
  renderer.getSpriteRenderer()->render(defeat);
  renderer.getSpriteRenderer()->render(arrow);

  renderer.render(window);
}

void DefeatState::deleteSave() {
  //TODO
}
