#include "tile.h"
#include "oak/core/resources.h"
#include "oak/core/store.h"

using namespace game;
using namespace oak;

Tile::Tile(int x, int y, std::string src, Collision collision, int id)
{
  this->id = id;
  this->x = x;
  this->y = y;
  this->src = src;
  this->collision = collision;
  Texture *texture = Resources::findTextureBySrc("test.png");
  this->textureID = texture->getID();
  this->shaderID = Resources::defaultShaderID;
  


  float xMin = ((float)(x * TILE_SIZE) / texture->getWidth());
  float yMin = ((float)(y * TILE_SIZE) / texture->getHeight());
  float xMax = ((float)((x + 1) * TILE_SIZE) / texture->getWidth());
  float yMax = ((float)((y + 1) * TILE_SIZE) / texture->getHeight());

  float screenW = (float)Store::window->getWidth();
  float screenH = (float)Store::window->getHeight();

  float halfSize = (float)(TILE_SIZE / 2);
  float xx = ((float)halfSize / screenH);
  float yy = ((float)halfSize / screenH);

  float vertices[] = {
    // positions          // texture coords
    -xx, -yy, 0.0f,  xMin, yMax, //bottom left
     xx, -yy, 0.0f,  xMax, yMax, //bottom right
     xx,  yy, 0.0f,  xMax, yMin, //top right

     xx,  yy, 0.0f,  xMax, yMin, //top right
    -xx,  yy, 0.0f,  xMin, yMin, //top left
    -xx, -yy, 0.0f,  xMin, yMax, //botom left
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

void Tile::onDraw(int tileCoorX, int tileCoorY)
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->textureID);
  glBindVertexArray(this->VAO);

  float screenW = (float)Store::window->getWidth();
  float screenH = (float)Store::window->getHeight();

  glm::mat4 model = glm::mat4(1.0);
  glm::vec3 pos(
    ((tileCoorX * TILE_SIZE) / screenH) - Store::camera->position.x,
    (-(tileCoorY * TILE_SIZE) / screenH) - Store::camera->position.y,
    0.0f
  );
  model = glm::translate(model, pos);

  Shader* shader = Resources::findShaderByID(this->shaderID);

  shader->setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);

}