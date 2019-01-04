#include "tile.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <oak/scene/camera.h>
#include <oak/window/window.h>
#include <oak/core/resources.h>

using namespace tile;
using namespace oak;

Tile::Tile(
  const uint tileID, 
  const Texture* texture,
  const uint TEX_COORD_X,
  const uint TEX_COORD_Y,
  const uint shaderID,
  const uint TILE_SIZE
) :
  tileID(tileID),
  textureID(texture->getID()),
  shaderID(shaderID)

{
  //texture coords
  float xMin = ((float)(TEX_COORD_X * TILE_SIZE) / texture->getWidth());
  float yMin = ((float)(TEX_COORD_Y * TILE_SIZE) / texture->getHeight());
  float xMax = ((float)((TEX_COORD_X + 1) * TILE_SIZE) / texture->getWidth());
  float yMax = ((float)((TEX_COORD_Y + 1) * TILE_SIZE) / texture->getHeight());

  //verticies dimension
  float screenH = (float)Window::getHeight();
  float halfSize = (float)(TILE_SIZE / 2);
  float d = Window::worldToViewportCoords(halfSize);

  float vertices[] = 
  {
    // positions          // texture coords
    -d, -d, 0.0f,  xMin, yMax, //bottom left
     d, -d, 0.0f,  xMax, yMax, //bottom right
     d,  d, 0.0f,  xMax, yMin, //top right

     d,  d, 0.0f,  xMax, yMin, //top right
    -d,  d, 0.0f,  xMin, yMin, //top left
    -d, -d, 0.0f,  xMin, yMax, //botom left
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void Tile::onRender(const float x, const float y) const
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->textureID);
  glBindVertexArray(this->VAO);


  glm::mat4 model = glm::mat4(1.0);

  glm::vec3 camNPos = Camera::getNormalizedPos();

  glm::vec3 pos(
    x - camNPos.x,
    y - camNPos.y,
    0.0f
  );
  model = glm::translate(model, pos);

  Shader* shader = oak::Resources::getShaderByID(shaderID);

  shader->setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);

}