#include "MainMenuState.h"

void MainMenuState::init(Window window) {
  renderer.init(window.getWidth(), window.getHeight());
  renderer.setClearColour(WHITE);
  
  title.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "main_menu_title.png");
  title.changeLocation(0.0f, 120.0f);
  title.changeScale(18.0f, 5.0f);
  
  arrow.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "arrow.png");
  arrow.changeLocation(65.0f, -29.0f);
}

void MainMenuState::updateState(enum Input input, GameStateManager *gameStateManager) {
  if (isOnNewGameButton && input == MENUDOWN) {
    arrow.changeLocation(0.0f, -70.0f);
    isOnNewGameButton = false;
  }
  
  if (!isOnNewGameButton && input == MENUUP) {
    arrow.changeLocation(0.0f, 70.0f);
    isOnNewGameButton = true;
  }
  
  if (input == MENUSELECT) {
    if (isOnNewGameButton) {
      gameStateManager->getSaveStateManager()->deleteSaveData();
      gameStateManager->enterNewState(stateCutScene);
    } else {
      arrow.changeLocation(0.0f, 70.0f);
      gameStateManager->getSaveStateManager()->loadSaveData(gameStateManager->getLevel(), gameStateManager->getPlayerX(), gameStateManager->getPlayerY(), gameStateManager->getHealth(), gameStateManager->getGridX(), gameStateManager->getGridY(), gameStateManager->getNumEncounters());
      gameStateManager->enterNewState(stateOverworld);
      isOnNewGameButton = true;
    }
  }
  
}

void MainMenuState::renderState(Window window) {
  renderer.clear();
  
  renderer.getFontRedererer()->renderText("New Game", -145.0f, -40.0f, 1.0f, SE_PURPLE);
  renderer.getFontRedererer()->renderText("Continue", -145.0f, -110.0f, 1.0f, SE_PURPLE);

  renderer.getSpriteRenderer()->render(arrow);
  renderer.getSpriteRenderer()->render(title);
  
  renderer.render(window);
}
