#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <stdlib.h>

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

#include "Shader.h"

class Sprite {
public:
  void loadSprite(std::string verticesDataFile, std::string texCoordsDataFile, std::string indicesDataFile, std::string textureFile);
  std::vector<GLfloat> getVertices();
  std::vector<GLfloat> getTexCoords();
  
  GLuint getVAO();
  GLuint getVBOVert();
  GLuint getVBOTex();
  GLuint getTexture();
  
  void changeLocation(float deltaX, float deltaY);
  void changeRotation(float angle);
  void changeScale(float scalar);
  void changeScale(float xScalar, float yScalar);
  void resetModel();
  
  glm::mat4 getModelMatrix();
  glm::mat4 getViewMatrix();
  glm::mat4 getScaleMatrix();
  
  void cleanup();
  
private:
  std::vector<GLfloat> loadArrayObjectData(std::string filename);
  std::vector<GLuint> loadElementArrayObjectData(std::string filename);
  void loadTextureData(std::string filename);
  
  GLuint texture;
  GLuint vao, vboVert, vboTex, ebo;
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 scale;
  glm::mat4 projection;
  std::vector<GLfloat> vertices;
  std::vector<GLfloat> texCoords;
  std::vector<GLuint> indices;
};

#endif
