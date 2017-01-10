#include "WeaponDropCutScene.h"

void WeaponDropCutScene::init(std::string filename1, std::string filename2, std::string filename3) {
  loadMessage(filename1, &weaponDropMessage1);
  loadMessage(filename2, &weaponDropMessage2);
  loadMessage(filename3, &weaponDropMessage3);
}

void WeaponDropCutScene::renderScene(FontRenderer *fontRenderer) {
  int j = 0;
  for (std::vector<std::string>::iterator i  = weaponDropMessage1.begin(); i != weaponDropMessage1.end(); i++) {
    fontRenderer->renderText(i->c_str(), -250.0f, 100.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
    j++;
  }
  for (std::vector<std::string>::iterator i  = weaponDropMessage2.begin(); i != weaponDropMessage2.end(); i++) {
    fontRenderer->renderText(i->c_str(), -250.0f, 100.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
    j++;
  }
  for (std::vector<std::string>::iterator i  = weaponDropMessage3.begin(); i != weaponDropMessage3.end(); i++) {
    fontRenderer->renderText(i->c_str(), -250.0f, 100.0f - j * 20.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
    j++;
  }
}
