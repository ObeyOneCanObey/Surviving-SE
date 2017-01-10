#include "PotionDropCutScene.h"

void PotionDropCutScene::init(std::string filename) {
  loadMessage(filename, &potionMessage);
}

void PotionDropCutScene::renderScene(FontRenderer *fontRenderer) {
  int j = 0;
  for (std::vector<std::string>::iterator i  = potionMessage.begin(); i != potionMessage.end(); i++) {
    fontRenderer->renderText(i->c_str(), -270.0f, 10.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
    j++;
  }
}
