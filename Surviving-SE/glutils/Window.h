#ifndef WINDOW_H
#define WINDOW_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

const GLuint WIDTH = 800, HEIGHT = 600;

class Window {
public:
  Window(int width = WIDTH, int height = HEIGHT);
  void init();
  GLFWwindow* getWindow();
  int getWidth();
  int getHeight();
  int getScreenWidth();
  int getScreenHeight();
  void cleanup();
private:
  GLFWwindow *window;
  int width, height;
  int SCREEN_WIDTH, SCREEN_HEIGHT;
};

#endif
