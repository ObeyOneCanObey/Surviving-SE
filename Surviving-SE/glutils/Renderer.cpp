#include "Renderer.h"

void Renderer::init(int width, int height) {
  spriteRenderer.init(width, height);
  fontRenderer.init(width, height);
}

void Renderer::clear() {
  glClearColor(clearColour.x, clearColour.y, clearColour.z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Window window) {
  glfwSwapBuffers(window.getWindow());
}

void Renderer::cleanup() {
  glfwTerminate();
  spriteRenderer.cleanup();
  fontRenderer.cleanup();
}

SpriteRenderer* Renderer::getSpriteRenderer() {
  return &spriteRenderer;
}

FontRenderer* Renderer::getFontRedererer() {
  return &fontRenderer;
}

void Renderer::setClearColour(glm::vec3 newClearColour) {
  clearColour = newClearColour;
}
