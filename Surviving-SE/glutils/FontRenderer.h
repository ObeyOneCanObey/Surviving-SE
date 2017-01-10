#ifndef FONTRENDERER_H
#define FONTRENDERER_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Freetype2
#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <iostream>
#include <string>

#include "Shader.h"

struct Character {
  GLuint textureID;
  glm::ivec2 size;
  glm::ivec2 bearing;
  GLuint advance;
};

//Renders font from TTF file and generates text to the window at specified location on the screen
class FontRenderer {
public:
  void init(int screenWidth, int screenHeight);
  void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 colour);
  void cleanup();
private:
  std::map<GLchar, Character> characters;
  Shader fontShader;
  GLuint vao, vboVert, vboTex;
  int screenWidth, screenHeight;
  glm::mat4 projection;
  glm::mat4 scaleMat;
};

#endif
