#ifndef BOSSCUTSCENE_H
#define BOSSCUTSCENE_H

#include "CutScene.h"
#include "Renderer.h"

//There is a intro boss fight cutscene, a cutscene for winning the fight, and one for losing
enum bossSceneState {
  INTRO = 0,
  WIN = 1,
  LOSS = 2
};

class BossCutScene : public CutScene {
public:
  void init(std::string filename1, std::string filename2, std::string filename3);
  void renderScene(FontRenderer *fontRenderer, enum bossSceneState scene);
private:
  std::vector<std::string> introMessage;
  std::vector<std::string> winMessage;
  std::vector<std::string> lossMessage;
};

#endif
