#include "tile.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <oak/scene/camera.h>
#include <oak/window/window.h>

#include <oak/debug.h>

using namespace tile;
using namespace oak;

Tile::Tile(
  const uint tileID, 
  const Texture* texture,
  const uint TEX_COORD_X,
  const uint TEX_COORD_Y,
  const uint TILE_SIZE,
  const uint spacing
) :
  tileID(tileID),
  textureID(texture->getID()),
  collisionRect(
    oak::CollisionRect(
      0.0f,
      0.0f,
      static_cast<float>(TILE_SIZE),
      static_cast<float>(TILE_SIZE)
    )
  )
{
  //texture coords
  const uint totalSize = (TILE_SIZE + spacing * 2);
  float xMin = (static_cast<float>(TEX_COORD_X * totalSize + spacing) / static_cast<float>(texture->getWidth()));
  float yMin = (static_cast<float>(TEX_COORD_Y * totalSize + spacing) / static_cast<float>(texture->getHeight()));
  float xMax = (static_cast<float>((TEX_COORD_X + 1) * totalSize - spacing) / static_cast<float>(texture->getWidth()));
  float yMax = (static_cast<float>((TEX_COORD_Y + 1) * totalSize - spacing) / static_cast<float>(texture->getHeight()));

  //verticies dimension
  float d = Window::worldToViewportCoords(static_cast<float>(TILE_SIZE));

  float vertices[] =
  {
    // positions          // texture coords
    0, -d, 0.0f,  xMin, yMax, //bottom left
    d, -d, 0.0f,  xMax, yMax, //bottom right
    d,  0, 0.0f,  xMax, yMin, //top right

    d,  0, 0.0f,  xMax, yMin, //top right
    0,  0, 0.0f,  xMin, yMin, //top left
    0, -d, 0.0f,  xMin, yMax, //botom left
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

void Tile::onRender(const float vpX, const float vpY, Shader* shader) const
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glBindVertexArray(VAO);

  glm::mat4 model = glm::mat4(1.0);

  glm::vec3 camNPos = Camera::getNormalizedPos();

  glm::vec3 pos(
    vpX - camNPos.x,
    vpY - camNPos.y,
    0.0f
  );

  model = glm::translate(model, pos);
  //shader->use();
  shader->setMat4("model", model);
  

  glDrawArrays(GL_TRIANGLES, 0, 6);
}