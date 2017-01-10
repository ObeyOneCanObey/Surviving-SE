#ifndef WEAPONDROPCUTSCENE_H
#define WEAPONDROPCUTSCENE_H

#include "CutScene.h"
#include "Renderer.h"

class WeaponDropCutScene : public CutScene {
public:
  void init(std::string filename1, std::string filename2, std::string filename3);
  void renderScene(FontRenderer *fontRenderer);
private:
  std::vector<std::string> weaponDropMessage1;
  std::vector<std::string> weaponDropMessage2;
  std::vector<std::string> weaponDropMessage3;
};
#endif
