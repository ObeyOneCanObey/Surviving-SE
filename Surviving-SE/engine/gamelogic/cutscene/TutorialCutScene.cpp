#include "TutorialCutScene.h"

void TutorialCutScene::init(std::string filename1, std::string filename2, std::string filename3, std::string filename4, std::string filename5, std::string filename6) {
  loadMessage(filename1, &tutorialIntro);
  loadMessage(filename2, &tutorialMovement);
  loadMessage(filename3, &tutorialMenu);
  loadMessage(filename4, &tutorialFight);
  loadMessage(filename5, &tutorialItems);
  loadMessage(filename6, &tutorialEnd);
}

void TutorialCutScene::renderScene(FontRenderer *fontRenderer, enum rollenTutorial tutorial) {
  int j = 0;
  
  switch (tutorial) {
    case TUT_INTRO:
      for (std::vector<std::string>::iterator i  = tutorialIntro.begin(); i != tutorialIntro.end(); i++) {
        fontRenderer->renderText(i->c_str(), -250.0f, 150.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
        j++;
      }
      break;
    case TUT_MOVEMENT:
      for (std::vector<std::string>::iterator i  = tutorialMovement.begin(); i != tutorialMovement.end(); i++) {
        fontRenderer->renderText(i->c_str(), -250.0f, 150.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
        j++;
      }
      break;
    case TUT_MENU:
      for (std::vector<std::string>::iterator i  = tutorialMenu.begin(); i != tutorialMenu.end(); i++) {
        fontRenderer->renderText(i->c_str(), -250.0f, 150.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
        j++;
      }
      break;
    case TUT_FIGHT:
      for (std::vector<std::string>::iterator i  = tutorialFight.begin(); i != tutorialFight.end(); i++) {
        fontRenderer->renderText(i->c_str(), -250.0f, 150.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
        j++;
      }
      break;
    case TUT_ITEMS:
      for (std::vector<std::string>::iterator i  = tutorialItems.begin(); i != tutorialItems.end(); i++) {
        fontRenderer->renderText(i->c_str(), -250.0f, 150.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
        j++;
      }
      break;
    case TUT_END:
      for (std::vector<std::string>::iterator i  = tutorialEnd.begin(); i != tutorialEnd.end(); i++) {
        fontRenderer->renderText(i->c_str(), -250.0f, 150.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
        j++;
      }
      break;
    default:
      break;
  }
}
