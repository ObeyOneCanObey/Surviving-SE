// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "engine/GameEngine.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

GameEngine engine;

void loadController();
int getControllerInput();
void init();
void gameLoop();
void cleanup();
void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mode);
void closeWindow();

int fileptr;

int main(void) {
  loadController();
  engine = GameEngine();
  init();
  gameLoop();
  cleanup();
  return EXIT_SUCCESS;
}

void init() {
  engine.init();
  glfwSetKeyCallback(engine.getWindowObject().getWindow(), keyCallBack);
}

void gameLoop() {
  while (!engine.isExitedGame()) {
    engine.getInput((enum Input) getControllerInput());
    engine.update();
    engine.render();
  }
}

void cleanup() {
  engine.cleanup();
}

// Opens serial port and initializes pointer to it
void loadController() {
  fileptr = open("/dev/tty.usbmodem0E218961", O_RDWR | O_NOCTTY | O_NDELAY);
  fcntl(fileptr, F_SETFL, 0);
  printf("Port has been successfully opened and the file description is %d\n", fileptr);
  
  if (fileptr == -1) {
    perror("Could not open serial port");
  }
}

// Read serial port data and returns byte that was sent
int getControllerInput() {
  int rd;
  unsigned char *buff = (unsigned char *) malloc(sizeof(unsigned char));
  rd = read(fileptr, buff, 1);
  if (rd != -1)
    return *buff;
  free(buff);
  return 0;
}

// Escape key closes game window
void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
