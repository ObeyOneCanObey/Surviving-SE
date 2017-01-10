#include "Window.h"

Window::Window(int width, int height) {
  this->width = width;
  this ->height = height;
}

void Window::init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  window = glfwCreateWindow(width, height, "Surviving SE", nullptr, nullptr);
  
  glfwMakeContextCurrent(window);
  
  glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    
  glewExperimental = GL_TRUE;
  glewInit();
  
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  
  glEnable(GL_DEPTH_TEST);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int Window::getWidth() {
  return width;
}

int Window::getHeight() {
  return height;
}

int Window::getScreenWidth() {
  return SCREEN_WIDTH;
}

int Window::getScreenHeight() {
  return SCREEN_HEIGHT;
}

GLFWwindow* Window::getWindow() {
  return window;
}

void Window::cleanup() {
  glfwDestroyWindow(window);
}
