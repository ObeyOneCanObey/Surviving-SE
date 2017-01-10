#ifndef SpriteRenderer_hpp
#define SpriteRenderer_hpp

#include "Shader.h"
#include "Sprite.h"

//Sprite renderer class to render a batch of sprites that are passed as params
class SpriteRenderer {
public:
  void init(int screenWidth, int screenHeight);
  void render(Sprite sprite);
  void cleanup();
private:
  Shader shader;
  glm::mat4 projection;
  glm::mat4 view;
  int screenWidth, screenHeight;
};

#endif
