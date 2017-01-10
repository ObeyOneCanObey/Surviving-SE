#include "BossCutScene.h"

void BossCutScene::init(std::string filename1, std::string filename2, std::string filename3) {
  loadMessage(filename1, &introMessage);
  loadMessage(filename2, &winMessage);
  loadMessage(filename3, &lossMessage);
}

void BossCutScene::renderScene(FontRenderer *fontRenderer, enum bossSceneState state) {
  int j = 0;
  switch (state) {
    case INTRO:
      for (std::vector<std::string>::iterator i = introMessage.begin(); i != introMessage.end(); i++) {
        fontRenderer->renderText(i->c_str(), -250.0f, 100.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
        j++;
      }
      break;
    case WIN:
      for (std::vector<std::string>::iterator i = winMessage.begin(); i != winMessage.end(); i++) {
        fontRenderer->renderText(i->c_str(), -250.0f, 100.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
        j++;
      }
      break;
    case LOSS:
      for (std::vector<std::string>::iterator i = lossMessage.begin(); i != lossMessage.end(); i++) {
        fontRenderer->renderText(i->c_str(), -250.0f, 100.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
        j++;
      }
      break;
    default:
      break;
  }
}
