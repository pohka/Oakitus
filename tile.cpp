#include "tile.h"
#include "oak/core/resources.h"
#include "oak/core/store.h"
#include "oak/core/window.h"

using namespace game;
using namespace oak;

Tile::Tile(int x, int y, std::string src, Collision collision, int id)
{
  this->id = id;
  this->x = x;
  this->y = y;
  this->collision = collision;
  Texture *texture = Resources::findTextureBySrc(src);
  this->textureID = texture->getID();
  this->shaderID = Resources::defaultShaderID;
  

  //texture coords
  float xMin = ((float)(x * TILE_SIZE) / texture->getWidth());
  float yMin = ((float)(y * TILE_SIZE) / texture->getHeight());
  float xMax = ((float)((x + 1) * TILE_SIZE) / texture->getWidth());
  float yMax = ((float)((y + 1) * TILE_SIZE) / texture->getHeight());

  //verticies dimension
  float screenH = (float)Window::getHeight();
  float halfSize = (float)(TILE_SIZE / 2);
  float d = Window::worldToViewportCoords(halfSize);

  float vertices[] = {
    // positions          // texture coords
    -d, -d, 0.0f,  xMin, yMax, //bottom left
     d, -d, 0.0f,  xMax, yMax, //bottom right
     d,  d, 0.0f,  xMax, yMin, //top right

     d,  d, 0.0f,  xMax, yMin, //top right
    -d,  d, 0.0f,  xMin, yMin, //top left
    -d, -d, 0.0f,  xMin, yMax, //botom left
  };

  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);

  glBindVertexArray(this->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

Tile::~Tile()
{
  glDeleteVertexArrays(1, &this->VAO);
  glDeleteBuffers(1, &this->VBO);
}

void Tile::onDraw(float x, float y)
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->textureID);
  glBindVertexArray(this->VAO);


  glm::mat4 model = glm::mat4(1.0);

  glm::vec3 camNPos = Store::camera->getNormalizedPos();

  glm::vec3 pos(
    x - camNPos.x,
    y - camNPos.y,
    0.0f
  );
  model = glm::translate(model, pos);

  Shader* shader = Resources::findShaderByID(this->shaderID);

  shader->setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);

}