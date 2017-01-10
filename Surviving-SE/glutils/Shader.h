#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {
public:
  Shader();
  //Loads shader files from file path
  Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
  void useShader();
  void disable();
  void cleanup();
  GLuint getProgram();
private:
  GLuint Program;
};

#endif
