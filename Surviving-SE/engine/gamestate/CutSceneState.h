#ifndef CUTSCENESTATE_H
#define CUTSCENESTATE_H

#include <vector>
#include <string>
#include <iostream>

#include "GameState.h"
#include "../gamelogic/cutscene/CutScene.h"
#include "../gamelogic/cutscene/TutorialCutScene.h"
#include "../gamelogic/cutscene/PotionDropCutScene.h"
#include "../gamelogic/cutscene/WeaponDropCutScene.h"
#include "../gamelogic/cutscene/BossCutScene.h"

#define NUM_CUT_SCENE 6

enum cutScene {
  ROLLEN_TUTORIAL = 0,
  WEAPON_DROP = 1,
  POTION_DROP = 2,
  BOSS_INTRO = 3,
  BOSS_WIN = 4,
  BOSS_LOSS = 5, 
  NO_SCENE = 6,
};

class CutSceneState : public GameState {
public:
  void init(Window window);
  void enterNewCutscene(enum cutScene cutscene);
  void updateState(enum Input input, GameStateManager *gameStateManager);
  void renderState(Window window);
  void updateTutorial();
  void renderTutorial();
  void renderBossCutScene(int level, enum bossSceneState state);
  
private:
  Sprite rollen;
  Sprite lam;
  Sprite morton;
  Sprite andre;
  Sprite mansour;
  Sprite speechBubble;
  
  enum cutScene currentScene = ROLLEN_TUTORIAL;
  enum rollenTutorial tutorialProgess = TUT_INTRO;
  bool isDoneTutorial = false;
  bool finishedBossIntro = false;
  
  TutorialCutScene rollenTut;
  BossCutScene mansourFight;
  BossCutScene lamFight;
  BossCutScene andreFight;
  BossCutScene mortonFight;
  
  WeaponDropCutScene seWeaponDrop;
  WeaponDropCutScene csWeaponDrop;
  WeaponDropCutScene mathWeaponDrop;
  WeaponDropCutScene eceWeaponDrop;
  PotionDropCutScene potionDrop;
  
};

#endif
