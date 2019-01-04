#include "chunk.h"
#include "world.h"
#include <oak/debug.h>
#include <oak/core/resources.h>
#include <oak/window/window.h>

using namespace tile;

Chunk::Chunk(const uint CHUNK_SIZE) : Component(TICK_GROUP_DEFAULT, TICK_TYPE_NOT_TICKABLE, true)
{
  //create rows
  table.resize(CHUNK_SIZE);

  //fill rows
  for (uint i=0; i<CHUNK_SIZE; i++)
  {
    table[i].resize(CHUNK_SIZE);
  }
}


Chunk::~Chunk()
{

}

void Chunk::onRender() const
{
  oak::Shader* shader = oak::Resources::getDefaultShader();
  uint id;
  Tile* tile;
  shader->use();

  float vpTileSize = oak::Window::worldToViewportCoords(world->TILE_SIZE);

  for (uint y = 0; y < table.size(); y++)
  {
    for (uint x = 0; x < table[y].size(); x++)
    {
      id = table[y][x];
      if (id != 0)
      {
        tile = world->getTileByID(id);
        if (tile != nullptr)
        {
          tile->onRender(
            (float)(x * vpTileSize),
            -(float)(y * vpTileSize),
            shader
          );
        }
      }
    }
  }
}