#include "FightState.h"

void FightState::init(Window window) {
  renderer.init(window.getWidth(), window.getHeight());
  renderer.setClearColour(WHITE);
  
  playerAvatar.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "PlayerBattleSprite.png");
  playerAvatar.changeScale(8.0f, 10.0f);
  playerAvatar.changeLocation(-200.0f, -150.0f);
  
  mainMenuArrow.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "arrow.png");
  mainMenuArrow.changeLocation(250.0f, -180.0f);

  attackMenuArrow.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "arrow.png");
  attackMenuArrow.changeLocation(170.0f, -180.0f);

  potionsMenuArrow.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "arrow.png");
  potionsMenuArrow.changeScale(0.5f);
  potionsMenuArrow.changeLocation(165.0f, -175.0f);
  
  monsterHPBar.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "border_white_fill.png");
  monsterHPBar.changeScale(10.0f, 5.0f);
  monsterHPBar.changeLocation(-175.0f, 150.0f);
  
  playerHPBar.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "border_white_fill.png");
  playerHPBar.changeScale(10.0f, 5.0f);
  playerHPBar.changeLocation(175.0f, -80.0f);
  
  playerFightMenu.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "border_white_fill.png");
  playerFightMenu.changeScale(10.0f, 5.0f);
  playerFightMenu.changeLocation(175.0f, -200.0f);

  
  createBossSprite(&seMonster, "textureVertices.csv", "textureCoords.csv", "indices.csv", "EasyGeeseSprite.png");
  createBossSprite(&csMonster, "textureVertices.csv", "textureCoords.csv", "indices.csv", "MediumGeeseSprite.png");
  createBossSprite(&mathMonster, "textureVertices.csv", "textureCoords.csv", "indices.csv", "HardGeeseSprite.png");
  createBossSprite(&eceMonster, "textureVertices.csv", "textureCoords.csv", "indices.csv", "HardGeeseSprite.png");
  
  createBossSprite(&lam, "textureVertices.csv", "textureCoords.csv", "indices.csv", "LamJobs.png");
  createBossSprite(&morton, "textureVertices.csv", "textureCoords.csv", "indices.csv", "MortonSchwarzernegger.png");
  createBossSprite(&andre, "textureVertices.csv", "textureCoords.csv", "indices.csv", "AndreWhite.png");
  createBossSprite(&mansour, "textureVertices.csv", "textureCoords.csv", "indices.csv", "MansourAlladeen.png");
  
  fight.updateCurrentLevel(level);
  fight.updateCurrentMonster(monsterEncounter, isBossFight);
  fight.setFightHealths(currentPlayerHealth);
  
  maxMonsterHealth = fight.getMonsterHealth();
}

void FightState::updateState(enum Input input, GameStateManager *gameStateManager) {

  currentPlayerHealth = fight.getPlayerHealth();
  std::cout << currentPlayerHealth << std::endl;
  
  if (isFirstMove) {
    fight.updateCurrentLevel(level);
    fight.updateCurrentMonster(monsterEncounter, isBossFight);
    fight.setFightHealths(currentPlayerHealth);
    maxMonsterHealth = fight.getMonsterHealth();
    isFirstMove = false;
  }
  
  currentMonsterHealth = fight.getMonsterHealth();
  
  if (inMainMenu) {
    if (input == MENUDOWN && cursorOnFight) {
      mainMenuArrow.changeLocation(0.0f, -40.0f);
      cursorOnFight = false;
    }
    if (input == MENUUP && !cursorOnFight) {
      mainMenuArrow.changeLocation(0.0f, 40.0f);
      cursorOnFight = true;
    }
    
    if (input == MENUSELECT && inMainMenu) {
      inMainMenu = false;
      if (cursorOnFight)
        inAttackMenu = true;
      else
        inPotionsMenu = true;
    }
  } else if (input == MENUBACK) {
    inAttackMenu = false;
    inPotionsMenu = false;
    
    resetCursor(&attackMenuArrow, attackCursor, attackCursorMovement);
    resetCursor(&potionsMenuArrow, potionsCursor, potionsCursorMovement);
    
    attackCursor = 0;
    potionsCursor = 0;
    
    inMainMenu = true;
  } else if (inAttackMenu) {
    if (input == MENUSELECT) {
      fight.updateHealth(true, attackCursor);
      
      resetCursor(&attackMenuArrow, attackCursor, attackCursorMovement);
      attackCursor = 0;
      
      inAttackMenu = false;
      inMainMenu = true;
      std::cout << inMainMenu;
    }
    if (input == MENUUP || input == MENUDOWN)
      moveMenuCursors(input, &attackCursor, &attackMenuArrow, attackCursorMovement);
  } else if (inPotionsMenu) {
    if (input == MENUSELECT && fight.getPotionCount(potionValues[potionsCursor])) {
      fight.updateHealth(false, potionsCursor);
      
      resetCursor(&potionsMenuArrow, potionsCursor, potionsCursorMovement);
      potionsCursor = 0;
      
      inPotionsMenu = false;
      inMainMenu = true;
    }
    if (input == MENUUP || input == MENUDOWN)
      moveMenuCursors(input, &potionsCursor, &potionsMenuArrow, potionsCursorMovement);
  }
  
  if (currentPlayerHealth == 0) {
    fight.setFightHealths(maxPlayerHealth);
    fight.deletePotions();
    isFirstMove = true;
    std::cout << "DEFEAT\n";
    gameStateManager->enterNewState(stateDefeat);
  }
  
  if (currentMonsterHealth == 0) {
    isFirstMove = true;
    inAttackMenu = false;
    inMainMenu = true;
    if (!isBossFight) {
      fight.generatePotion();
    }
    if (isBossFight) {
      std::cout << "BOSS FIGHT";
      gameStateManager->updateGameStateParams(level + 1, monsterEncounter, numMonsterEncounters, true, maxPlayerHealth, false, false);
      currentPlayerHealth = maxPlayerHealth;
      fight.setFightHealths(maxPlayerHealth);
      std::cout << currentPlayerHealth << std::endl;
    }
    gameStateManager->enterNewState(stateOverworld);
    
  }
}

void FightState::renderState(Window window) {
  renderer.clear();
  
  renderFightMenu();
  
  renderHealthBars(&currentPlayerHealth, &currentMonsterHealth, &renderer);
  
  renderer.getSpriteRenderer()->render(playerAvatar);
  
  if (isBossFight) {
    switch (level) {
      case 0:
        renderer.getSpriteRenderer()->render(lam);
        break;
      case 1:
        renderer.getSpriteRenderer()->render(morton);
        break;
      case 2:
        renderer.getSpriteRenderer()->render(andre);
        break;
      case 3:
        renderer.getSpriteRenderer()->render(mansour);
        break;
      default:
        break;
    }
  } else {
    switch (level) {
      case 0:
        renderer.getSpriteRenderer()->render(seMonster);
        break;
      case 1:
        renderer.getSpriteRenderer()->render(csMonster);
        break;
      case 2:
        renderer.getSpriteRenderer()->render(mathMonster);
        break;
      case 3:
        renderer.getSpriteRenderer()->render(eceMonster);
        break;
      default:
        break;
    }
  }
  
  renderer.render(window);
}

void FightState::createBossSprite(Sprite *sprite, std::string verticesDataFile, std::string texCoordsDataFile, std::string indicesDataFile, std::string textureFile) {
  sprite->loadSprite(verticesDataFile, texCoordsDataFile, indicesDataFile, textureFile);
  sprite->changeScale(8.0f, 10.0f);
  sprite->changeLocation(225.0f, 150.0f);
}

void FightState::setFightParams(int level, int monsterEncounter) {
  this->level = level;
  this->monsterEncounter = monsterEncounter;
}
  
void FightState::renderHealthBars(int *currentPlayerHealth, int *currentMonsterHealth, Renderer *renderer) {
  *currentPlayerHealth = fight.getPlayerHealth();
  *currentMonsterHealth = fight.getMonsterHealth();
  
  renderer->getFontRedererer()->renderText("HP: " + std::to_string(*currentMonsterHealth) + " / " + std::to_string(maxMonsterHealth), -300.0f, 140.0f, 1.0f, BLACK);
  
  renderer->getFontRedererer()->renderText("HP: " + std::to_string(*currentPlayerHealth) + " / " + std::to_string(maxPlayerHealth), 50.0f, -95.0f, 1.0f, BLACK);
  
  renderer->getSpriteRenderer()->render(monsterHPBar);
  renderer->getSpriteRenderer()->render(playerHPBar);
  renderer->getSpriteRenderer()->render(playerFightMenu);

}

void FightState::renderFightMenu() {
  if (inMainMenu) {
    renderer.getSpriteRenderer()->render(mainMenuArrow);
    
    renderer.getFontRedererer()->renderText("Fight", 50.0f, -190.0f, 0.8f, BLACK);
  
    renderer.getFontRedererer()->renderText("Potion", 50.0f, -230.0f, 0.8f, BLACK);
    
  } else if (inAttackMenu) {
    renderer.getSpriteRenderer()->render(attackMenuArrow);
    
    renderer.getFontRedererer()->renderText(weapons[level * 3], 50.0f, -190.0f, 0.8f, BLACK);
    
    renderer.getFontRedererer()->renderText(weapons[level * 3 + 1], 50.0f, -230.0f, 0.8f, BLACK);

    renderer.getFontRedererer()->renderText(weapons[level * 3 + 2], 200.0f, -190.0f, 0.8f, BLACK);

  } else {
    renderer.getSpriteRenderer()->render(potionsMenuArrow);
    
    renderer.getFontRedererer()->renderText(potions[0] + " x " + "(" + std::to_string(fight.getPotionCount(potionValues[0])) + ")", 50.0f, -180.0f, 0.35f, BLACK);
    
    renderer.getFontRedererer()->renderText(potions[1] + " x " + "(" + std::to_string(fight.getPotionCount(potionValues[1])) + ")", 50.0f, -220.0f, 0.35f, BLACK);
    
    renderer.getFontRedererer()->renderText(potions[2] + " x " + "(" + std::to_string(fight.getPotionCount(potionValues[2])) + ")", 180.0f, -180.0f, 0.35f, BLACK);
    
  }
}

void FightState::moveMenuCursors(enum Input input, int *cursorValue, Sprite *cursor, float cursorMovement[2][2]) {
  if (input == MENUUP) {
    switch (*cursorValue) {
      case 0:
        break;
      case 1:
        *cursorValue = *cursorValue - 1;
        cursor->changeLocation(cursorMovement[0][0], cursorMovement[0][1]);
        break;
      case 2:
        *cursorValue = *cursorValue - 1;
        cursor->changeLocation(cursorMovement[1][0], cursorMovement[1][1]);
        break;
      default:
        break;
    }
  }
  
  if (input == MENUDOWN) {
    switch (*cursorValue) {
      case 0:
        *cursorValue = *cursorValue + 1;
        cursor->changeLocation(-cursorMovement[0][0], -cursorMovement[0][1]);
        break;
      case 1:
        *cursorValue = *cursorValue + 1;
        cursor->changeLocation(-cursorMovement[1][0], -cursorMovement[1][1]);
        break;
      case 2:
        break;
      default:
        break;
    }
  }
}

void FightState::resetCursor(Sprite *cursor, int cursorValue, float cursorMovement[2][2]) {
  switch (cursorValue) {
    case 0:
      break;
    case 1:
      cursor->changeLocation(0.0f, cursorMovement[0][1]);
      break;
    case 2:
      cursor->changeLocation(cursorMovement[1][0], 0.0f);
      break;
      
    default:
      break;
  }
}

void FightState::updateGameStateParams(GameStateManager *gameStateManager, int monsterEncounter, int level, int numMonsterEncounters, bool isNewGame, bool isFight) {
  gameStateManager->updateGameStateParams(level, monsterEncounter, numMonsterEncounters, isNewGame, currentPlayerHealth, isFight, isBossFight);
}


