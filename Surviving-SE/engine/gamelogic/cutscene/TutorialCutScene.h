#ifndef TUTORIALCUTSCENE_H
#define TUTORIALCUTSCENE_H

#include "CutScene.h"
#include "Renderer.h"

//There are six parts of the tutorial cut scene to render
enum rollenTutorial {
  TUT_INTRO = 0,
  TUT_MOVEMENT = 1,
  TUT_MENU = 2,
  TUT_FIGHT = 3,
  TUT_ITEMS = 4,
  TUT_END = 5
};

class TutorialCutScene : public CutScene {
public:
  void init(std::string filename1, std::string filename2, std::string filename3, std::string filename4, std::string filename5, std::string filename6);
  void renderScene(FontRenderer *fontRenderer, enum rollenTutorial tutorial);
private:
  std::vector<std::string> tutorialIntro;
  std::vector<std::string> tutorialMovement;
  std::vector<std::string> tutorialMenu;
  std::vector<std::string> tutorialFight;
  std::vector<std::string> tutorialItems;
  std::vector<std::string> tutorialEnd;
};

#endif
