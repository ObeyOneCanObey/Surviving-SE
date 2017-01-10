#include "SpriteRenderer.h"

// Sets up sprite renderer to output to window
void SpriteRenderer::init(int screenWidth, int screenHeight) {
  shader = Shader("res/shaders/sprite.vert", "res/shaders/sprite.frag");
  
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
  
  projection = glm::ortho((GLfloat) -screenWidth / 2.0f, (GLfloat) screenWidth / 2.0f, (GLfloat) -screenHeight / 2.0f, (GLfloat) screenHeight / 2.0f, -1.0f, 1.0f);
  view = glm::mat4();
}

// Renders sprite to window
void SpriteRenderer::render(Sprite sprite) {
  shader.useShader();
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, sprite.getTexture());
  glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture1"), 0);
  
  GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
  GLint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
  GLint projLoc = glGetUniformLocation(shader.getProgram(), "projection");
  GLint scaleLoc = glGetUniformLocation(shader.getProgram(), "scale");
  
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(sprite.getModelMatrix()));
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(sprite.getScaleMatrix()));
  
  glBindVertexArray(sprite.getVAO());
  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  
  glBindVertexArray(0);
  
  shader.disable();
}

void SpriteRenderer::cleanup() {
  shader.cleanup();
}
