#include "InGameMenuState.h"

void InGameMenuState::init(Window window) {
  renderer.init(window.getWidth(), window.getHeight());
  renderer.setClearColour(WHITE);
  
  arrow.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "arrow.png");
  arrow.changeLocation(250.0f, 60.0f);

  menuBorder.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "border_white_fill.png");
  menuBorder.changeScale(25.0f, 25.0f);
}

void InGameMenuState::updateState(enum Input input, GameStateManager *gameStateManager) {
  if (!returnToMenu && input == MENUDOWN) {
    arrow.changeLocation(0.0f, -100.0f);
    returnToMenu = true;
  }
  
  if (returnToMenu && input == MENUUP) {
    arrow.changeLocation(0.0f, 100.0f);
    returnToMenu = false;
  }
  
  if (input == MENUSELECT) {
    gameStateManager->getSaveStateManager()->recordSaveData(level, playerX, playerY, health, gridX, gridY, numMonsterEncounters);
    if (returnToMenu) {
      returnToMenu = false;
      arrow.changeLocation(0.0f, 100.0f);
      gameStateManager->enterNewState(stateMainMenu);
    }
  }
  
  if (input == FLIPSWITCHDOWN) {
    if (returnToMenu) {
      returnToMenu = false;
      arrow.changeLocation(0.0f, 100.0f);
    }
    gameStateManager->enterNewState(stateOverworld);
  }
}

void InGameMenuState::renderState(Window window) {
  renderer.clear();
  
  renderer.getSpriteRenderer()->render(arrow);
  
  renderer.getFontRedererer()->renderText("Save and continue", -250.0f, 50.0f, 0.8f, BLACK);
  renderer.getFontRedererer()->renderText("Save and return to main menu", -250.0f, -50.0f, 0.8f, BLACK);
  
  renderer.getSpriteRenderer()->render(menuBorder);
  
  renderer.render(window);
}
