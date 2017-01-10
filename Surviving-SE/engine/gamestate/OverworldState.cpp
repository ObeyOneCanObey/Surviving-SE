#include "OverworldState.h"

void OverworldState::init(Window window) {
  renderer.init(window.getWidth(), window.getHeight());
  renderer.setClearColour(LIGHT_GREY);
  
  playerAvater.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "PlayerSprite.png");
  wall.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "wall.png");
  
  seMonster.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "EasyGeese.png");
  csMonster.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "MediumGeese.png");
  mathMonster.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "HardGeese.png");
  eceMonster.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "HardGeese.png");
  
  overworld.initMap();
  currentPlayerPos = overworld.getPlayerPos();
  currentGridPos = overworld.getGridCoords();
}

void OverworldState::updateState(enum Input input, GameStateManager *gameStateManager) {
  if (level == 4) {
    gameStateManager->enterNewState(stateVictory);
  }
  
  if (isNewLevel) {
    overworld.resetOverworld();
    isNewLevel = false;
    updateGameStateParams(gameStateManager, overworld.getMonsterEncounter(), level, overworld.getNumMonsterEncounters(), isNewLevel, isFight, overworld.isMonsterFight());
  }
  
  bool isBossFight = overworld.isBossFight();
  std::cout << isBossFight << std::endl;
  if (isBossFight || overworld.isMonsterFight()) {
    updateGameStateParams(gameStateManager, overworld.getMonsterEncounter(), level, overworld.getNumMonsterEncounters(), isNewLevel, isFight, overworld.isMonsterFight());
    updateBossParams(gameStateManager, isBossFight);
    gameStateManager->enterNewState(stateFight);
  }
  
  switch (input) {
    case FLIPSWITCHUP:
      gameStateManager->enterNewState(stateInGameMenu);
      break;
    case UP:
      overworld.updateMap(MOVE_UP);
      break;
    case DOWN:
      overworld.updateMap(MOVE_DOWN);
      break;
    case LEFT:
      overworld.updateMap(MOVE_LEFT);
      break;
    case RIGHT:
      overworld.updateMap(MOVE_RIGHT);
      break;
    case UPLEFT:
      overworld.updateMap(MOVE_UPLEFT);
      break;
    case UPRIGHT:
      overworld.updateMap(MOVE_UPRIGHT);
      break;
    case DOWNLEFT:
      overworld.updateMap(MOVE_DOWNLEFT);
      break;
    case DOWNRIGHT:
      overworld.updateMap(MOVE_DOWNRIGHT);
      break;
    default:
      break;
  }
  updatePlayerPos();
  updateMapContents();
  currentPlayerPos = overworld.getPlayerPos();
  currentGridPos = overworld.getGridCoords();
  gameStateManager->updateLocationParams(currentPlayerPos.xpos, currentPlayerPos.ypos, currentGridPos.xpos, currentGridPos.ypos);
}

void OverworldState::renderState(Window window) {
  renderer.clear();
  
  playerAvater.resetModel();
  playerAvater.changeLocation(MOVE_TO_ORIGIN);
  playerAvater.changeLocation(currentPlayerPos.xpos * GRID_WIDTH, currentPlayerPos.ypos * GRID_HEIGHT);
  renderer.getSpriteRenderer()->render(playerAvater);
    
  for (int i = 0; i < MAP_WIDTH; i++) {
    for (int j = 0; j < MAP_HEIGHT; j++) {
      if (overworldMap[i * MAP_WIDTH + j] == WALL) {
        wall.resetModel();
        wall.changeLocation(MOVE_TO_ORIGIN);
        wall.changeLocation(i * GRID_WIDTH, j * GRID_HEIGHT);
        renderer.getSpriteRenderer()->render(wall);
      } else if (overworldMap[i * MAP_WIDTH + j] != 0) {
        switch (level) {
          case 0:
            renderer.getFontRedererer()->renderText("SE", -380, 250, 1.0f, SE_PURPLE);
            seMonster.resetModel();
            seMonster.changeLocation(MOVE_TO_ORIGIN);
            seMonster.changeLocation(i * GRID_WIDTH, j * GRID_HEIGHT);
            renderer.getSpriteRenderer()->render(seMonster);
          break;

          case 1:
            renderer.getFontRedererer()->renderText("CS", -380, 250, 1.0f, SE_PURPLE);
            csMonster.resetModel();
            csMonster.changeLocation(MOVE_TO_ORIGIN);
            csMonster.changeLocation(i * GRID_WIDTH, j * GRID_HEIGHT);
            renderer.getSpriteRenderer()->render(csMonster);
          break;
          
          case 2:
            renderer.getFontRedererer()->renderText("MATH", -380, 250, 1.0f, SE_PURPLE);
            mathMonster.resetModel();
            mathMonster.changeLocation(MOVE_TO_ORIGIN);
            mathMonster.changeLocation(i * GRID_WIDTH, j * GRID_HEIGHT);
            renderer.getSpriteRenderer()->render(mathMonster);
          break;
          
          case 3:
            renderer.getFontRedererer()->renderText("ECE", -380, 250, 1.0f, SE_PURPLE);
            eceMonster.resetModel();
            eceMonster.changeLocation(MOVE_TO_ORIGIN);
            eceMonster.changeLocation(i * GRID_WIDTH, j * GRID_HEIGHT);
            renderer.getSpriteRenderer()->render(eceMonster);
          break;

          default:
          break;
        }
      }
    }
  }
  
  renderer.render(window);
}

void OverworldState::updateMapContents() {
  int *updatedMap = (int *) malloc(sizeof(int) * MAP_HEIGHT * MAP_WIDTH);
  updatedMap = overworld.getMap();
  for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
    *(overworldMap + i) = *(updatedMap + i);
  }
}

void OverworldState::updatePlayerPos() {
  currentPlayerPos = overworld.getPlayerPos();
}

void OverworldState::updateGameStateParams(GameStateManager *gameStateManager, int monsterEncounter, int level, int numMonsterEncounters, bool isNewLevel, bool isFight, bool isMonsterFight) {
  gameStateManager->updateGameStateParams(level, monsterEncounter, numMonsterEncounters, isNewLevel, health, isFight, isMonsterFight);
}

void OverworldState::updateBossParams(GameStateManager *gameStateManager, bool isBossFight) {
  gameStateManager->updateBossFightParams(isBossFight, isBeatenBoss);
}
