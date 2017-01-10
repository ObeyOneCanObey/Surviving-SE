#include "CutSceneState.h"

void CutSceneState::init(Window window) {
  renderer.init(window.getWidth(), window.getHeight());
  renderer.setClearColour(WHITE);
  
  rollen.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "RollenDsouza.png");
  rollen.changeScale(6.0f, 8.0f);
  rollen.changeLocation(-300.0f, -200.0f);
  
  lam.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "PatrickLam.png");
  lam.changeScale(6.0f, 8.0f);
  lam.changeLocation(-300.0f, -200.0f);
  
  morton.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "AndrewMorton.png");
  morton.changeScale(6.0f, 8.0f);
  morton.changeLocation(-300.0f, -200.0f);
  
  andre.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "RobertAndre.png");
  andre.changeScale(6.0f, 8.0f);
  andre.changeLocation(-300.0f, -200.0f);
  
  mansour.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "FirasMansour.png");
  mansour.changeScale(6.0f, 8.0f);
  mansour.changeLocation(-300.0f, -200.0f);
  
  speechBubble.loadSprite("textureVertices.csv", "textureCoords.csv", "indices.csv", "speech-bubble.png");
  speechBubble.changeScale(20.0f, 20.0f);
  
  rollenTut.init("rollen_tutorial_intro.txt", "rollen_tutorial_movement.txt", "rollen_tutorial_menu.txt", "rollen_tutorial_fight.txt", "rollen_tutorial_items.txt", "rollen_tutorial_end.txt");
  mansourFight.init("mansour_fight.txt", "mansour_fight_win.txt", "mansour_fight_loss.txt");
  lamFight.init("lam_fight.txt", "lam_fight_win.txt", "lam_fight_loss.txt");
  andreFight.init("andre_fight.txt", "andre_fight_win.txt", "andre_fight_loss.txt");
  mortonFight.init("morton_fight.txt", "morton_fight_win.txt", "morton_fight_loss.txt");
  
  seWeaponDrop.init("se_weapon_drop1.txt", "se_weapon_drop2.txt", "se_weapon_drop3.txt");
  csWeaponDrop.init("cs_weapon_drop1.txt", "cs_weapon_drop2.txt", "cs_weapon_drop3.txt");
  mathWeaponDrop.init("math_weapon_drop1.txt", "math_weapon_drop2.txt", "math_weapon_drop3.txt");
  eceWeaponDrop.init("ece_weapon_drop1.txt", "ece_weapon_drop2.txt", "ece_weapon_drop3.txt");
  potionDrop.init("potion_drop.txt");
}

void CutSceneState::enterNewCutscene(enum cutScene cutscene) {
  currentScene = cutscene;
}

void CutSceneState::updateState(enum Input input, GameStateManager *gameStateManager) {
  
  if (!isDoneTutorial)
    currentScene = ROLLEN_TUTORIAL;
  
  if ((input == MENUSELECT || input == MENUBACK || input == MENUUP || input == MENUDOWN) && tutorialProgess != TUT_END)
    updateTutorial();
  
  if (input == FLIPSWITCHDOWN && tutorialProgess == TUT_END) {
    tutorialProgess = TUT_INTRO;
    isDoneTutorial = true;
    gameStateManager->enterNewState(stateOverworld);
  }
}

void CutSceneState::renderState(Window window) {
  renderer.clear();
  
  switch (currentScene) {
    case ROLLEN_TUTORIAL:
      renderTutorial();
      break;
    case WEAPON_DROP:
      switch (level) {
        case 0:
          csWeaponDrop.renderScene(renderer.getFontRedererer());
          break;
        case 1:
          mathWeaponDrop.renderScene(renderer.getFontRedererer());
          break;
        case 2:
          eceWeaponDrop.renderScene(renderer.getFontRedererer());
          break;
        default:
          break;
      }
      break;
    case POTION_DROP:
      potionDrop.renderScene(renderer.getFontRedererer());
      break;
    case BOSS_INTRO:
      renderBossCutScene(level, INTRO);
      break;
    case BOSS_WIN:
      renderBossCutScene(level, WIN);
      break;
    case BOSS_LOSS:
      renderBossCutScene(level, LOSS);
      break;
    default:
      break;
  }
  
  renderer.render(window);
}

void CutSceneState::updateTutorial() {
  switch (tutorialProgess) {
    case TUT_INTRO:
      tutorialProgess = TUT_MOVEMENT;
      break;
    case TUT_MOVEMENT:
      tutorialProgess = TUT_MENU;
      break;
    case TUT_MENU:
      tutorialProgess = TUT_FIGHT;
      break;
    case TUT_FIGHT:
      tutorialProgess = TUT_ITEMS;
      break;
    case TUT_ITEMS:
      isDoneTutorial = true;
      tutorialProgess = TUT_END;
      break;
    default:
      break;
  }
}


void CutSceneState::renderTutorial() {
  renderer.getSpriteRenderer()->render(rollen);
  switch (tutorialProgess) {
    case TUT_INTRO:
      rollenTut.renderScene(renderer.getFontRedererer(), tutorialProgess);
      break;
    case TUT_MOVEMENT:
      rollenTut.renderScene(renderer.getFontRedererer(), tutorialProgess);
      break;
    case TUT_MENU:
      rollenTut.renderScene(renderer.getFontRedererer(), tutorialProgess);
      break;
    case TUT_FIGHT:
      rollenTut.renderScene(renderer.getFontRedererer(), tutorialProgess);
      break;
    case TUT_ITEMS:
      rollenTut.renderScene(renderer.getFontRedererer(), tutorialProgess);
      break;
    case TUT_END:
      rollenTut.renderScene(renderer.getFontRedererer(), tutorialProgess);
      break;
    default:
      break;
  }
  renderer.getSpriteRenderer()->render(speechBubble);
}

void CutSceneState::renderBossCutScene(int level, enum bossSceneState state) {
  switch (level) {
    case 0:
      renderer.getSpriteRenderer()->render(lam);
      lamFight.renderScene(renderer.getFontRedererer(), state);
      break;
    case 1:
      renderer.getSpriteRenderer()->render(morton);
      mortonFight.renderScene(renderer.getFontRedererer(), state);
      break;
    case 2:
      renderer.getSpriteRenderer()->render(andre);
      andreFight.renderScene(renderer.getFontRedererer(), state);
      break;
    case 3:
      renderer.getSpriteRenderer()->render(mansour);
      mansourFight.renderScene(renderer.getFontRedererer(), state);
      break;
    default:
      break;
  }
  renderer.getSpriteRenderer()->render(speechBubble);
}



