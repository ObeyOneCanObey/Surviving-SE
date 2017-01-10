#include "Sprite.h"

void Sprite::loadSprite(std::string verticesDataFile, std::string texCoordsDataFile, std::string indicesDataFile, std::string textureFile) {
  
  vertices = loadArrayObjectData(verticesDataFile);
  texCoords = loadArrayObjectData(texCoordsDataFile);
  indices = loadElementArrayObjectData(indicesDataFile);
  
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vboVert);
  glGenBuffers(1, &vboTex);
  glGenBuffers(1, &ebo);
  
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vboVert);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (GLfloat), &vertices.front(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, vboTex);
  glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof (GLfloat), &texCoords.front(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), ( GLvoid *) 0);
  glEnableVertexAttribArray(1);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof (GLuint), &indices.front(), GL_STATIC_DRAW);
  
  glBindVertexArray(0);
  
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  loadTextureData(textureFile);
  
  model = glm::mat4();
  scale = glm::scale(glm::mat4(), glm::vec3(32, 24, 1));
}

std::vector<GLfloat> Sprite::loadArrayObjectData(std::string filename) {
  std::vector<GLfloat> data;
  
  std::ifstream arrayObjectStream;
  arrayObjectStream.open(std::string(("res/vertices/") + filename).c_str());
  
  if (arrayObjectStream.fail()) {
    std::cout << "ERROR:COULD_NOT_OPEN_FILE" << filename.c_str() << std::endl;
  }
  
  std::string objectValue;
  
  while (!arrayObjectStream.eof()) {
    getline(arrayObjectStream, objectValue, ',');
    data.push_back((GLfloat) atof(objectValue.c_str()));
  }
  
  return data;
}

std::vector<GLuint> Sprite::loadElementArrayObjectData(std::string filename) {
  std::vector<GLuint> data;
  
  std::ifstream arrayObjectStream;
  arrayObjectStream.open(std::string(("res/vertices/") + filename).c_str());
  
  if (arrayObjectStream.fail()) {
    std::cout << "ERROR:COULD_NOT_OPEN_FILE" << filename.c_str() << std::endl;
  }
  
  std::string objectValue;
  
  while (!arrayObjectStream.eof()) {
    getline(arrayObjectStream, objectValue, ',');
    data.push_back((GLuint) atoi(objectValue.c_str()));
  }
  
  return data;
}


void Sprite::loadTextureData(std::string filename) {
  int width, height;
  unsigned char *image = SOIL_load_image((std::string("res/images/") + filename).c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);
}

std::vector<GLfloat> Sprite::getVertices() {
  return vertices;
}

std::vector<GLfloat> Sprite::getTexCoords() {
  return texCoords;
}

GLuint Sprite::getVAO() {
  return vao;
}

GLuint Sprite::getVBOVert() {
  return vboVert;
}

GLuint Sprite::getVBOTex() {
  return vboTex;
}

GLuint Sprite::getTexture() {
  return texture;
}

void Sprite::changeLocation(float deltaX, float deltaY) {
  model = glm::translate(model, glm::vec3(deltaX, deltaY, 0));
}

void Sprite::changeScale(float scalar) {
  scale = glm::scale(scale, glm::vec3(scalar, scalar, 1.0f));
}

void Sprite::changeScale(float xScalar, float yScalar) {
  scale = glm::scale(scale, glm::vec3(xScalar, yScalar, 1.0f));
}

void Sprite::resetModel() {
  model = glm::mat4();
}

glm::mat4 Sprite::getModelMatrix() {
  return model;
}

glm::mat4 Sprite::getViewMatrix() {
  return view;
}

glm::mat4 Sprite::getScaleMatrix() {
  return scale;
}

void Sprite::cleanup() {
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
