#include "GameEngine.h"

void GameEngine::init() {
  window.init();
  gameStateManager.init(window);
}

void GameEngine::getInput(enum Input inputValue) {
  glfwPollEvents();
  this->inputValue = inputValue;
}

void GameEngine::update() {
  gameStateManager.getCurrentState()->updateState(inputValue, &gameStateManager);
}

void GameEngine::render() {
  gameStateManager.getCurrentState()->renderState(window);
}

void GameEngine::cleanup() {
  glfwTerminate();
  gameStateManager.cleanup();
  window.cleanup();
}

bool GameEngine::isExitedGame() {
  return glfwWindowShouldClose(window.getWindow());
}

Window GameEngine::getWindowObject() {
  return window;
}

GameStateManager GameEngine::getGameStateManager() {
  return gameStateManager;
}
