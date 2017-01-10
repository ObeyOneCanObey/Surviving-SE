#ifndef POTIONDROPCUTSCENE_H
#define POTIONDROPCUTSCENE_H

#include <iostream>

#include "CutScene.h"
#include "Renderer.h"

class PotionDropCutScene : public CutScene {
public:
  void init(std::string filename);
  void renderScene(FontRenderer *fontRenderer);
private:
  std::vector<std::string> potionMessage;
};

#endif
