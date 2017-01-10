#include "FontRenderer.h"

// Initializes font redererer
void FontRenderer::init(int screenWidth, int screenHeight) {
  fontShader = Shader("res/shaders/text.vert", "res/shaders/text.frag");
  
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
  
  // Initializes Freetype library object
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "ERROR::FREETYPE: Count not init FREETYPE Library" << std::endl;
  FT_Face face;
  if (FT_New_Face(ft, "res/fonts/clacon.ttf", 0, &face))
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
  
  FT_Set_Pixel_Sizes(face, 0, 48);
  
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  // Loads information about each glyph and stores in Character struct
  for (GLubyte c = 0; c < 128; c++) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
      continue;
    }
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    Character character = {
      texture,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      (GLuint) face->glyph->advance.x
    };
    // map stores the pair for the ASCII char and font information
    characters.insert(std::pair<GLchar, Character>(c, character));
  }
  
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vboVert);
  glGenBuffers(1, &vboTex);
  
  glBindVertexArray(vao);
  
  glBindBuffer(GL_ARRAY_BUFFER, vboVert);
  glBufferData(GL_ARRAY_BUFFER, 2 * 6 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, vboTex);
  glBufferData(GL_ARRAY_BUFFER, 2 * 6 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  projection = glm::ortho((GLfloat) -screenWidth / 2.0f, (GLfloat) screenWidth / 2.0f, (GLfloat) -screenHeight / 2.0f, (GLfloat) screenHeight / 2.0f, -1.0f, 1.0f);
  
}

// Renders text by iterating through chars of string and drawing texture based on char information
void FontRenderer::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 colour) {
  fontShader.useShader();
  
  glUniform3f(glGetUniformLocation(fontShader.getProgram(), "textColour"), colour.x, colour.y, colour.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vao);
  
  GLint projectionLoc = glGetUniformLocation(fontShader.getProgram(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
  
  for (std::string::const_iterator c = text.begin(); c != text.end(); c++) {
    Character ch = characters[*c];
    
    GLfloat xpos = x + ch.bearing.x * scale;
    GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;
    
    GLfloat width = ch.size.x * scale;
    GLfloat height = ch.size.y * scale;
    
    GLfloat vertices[6][2] = {
      {xpos,          ypos + height },
      {xpos,          ypos          },
      {xpos + width,  ypos          },
      {xpos,          ypos + height },
      {xpos + width,  ypos          },
      {xpos + width,  ypos + height }
    };
    
    GLfloat texCoords[6][2] = {
      {0.0, 0.0},
      {0.0, 1.0},
      {1.0, 1.0},
      {0.0, 0.0},
      {1.0, 1.0},
      {1.0, 0.0}
    };
    
    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    glBindBuffer(GL_ARRAY_BUFFER, vboVert);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(texCoords), texCoords);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    x += (ch.advance >> 6) * scale;
  }
  
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  fontShader.disable();
}

void FontRenderer::cleanup() {
  fontShader.cleanup();
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}




