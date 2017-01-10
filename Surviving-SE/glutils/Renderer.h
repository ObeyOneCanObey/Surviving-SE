#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "../SOIL2/SOIL2.h"

// Other includes
#include "Shader.h"
#include "Sprite.h"
#include "Window.h"
#include "FontRenderer.h"
#include "SpriteRenderer.h"

//General renderer class in charge of text and sprite rendering
class Renderer {
public:
  void init(int width, int height);
  void clear();
  void render(Window window);
  void cleanup();
  void setClearColour(glm::vec3 newClearColour);
  SpriteRenderer* getSpriteRenderer();
  FontRenderer* getFontRedererer();
private:
  SpriteRenderer spriteRenderer;
  FontRenderer fontRenderer;
  glm::vec3 clearColour;
};
#endif
