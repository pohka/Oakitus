#include "chunk_script.h"
#include "tile.h"
#include <oak/core/resources.h>
#include <oak/window/window.h>
#include "world.h"
#include <oak/components/rigid_body_2d.h>

using namespace tile;
using namespace oak;

ChunkScript::ChunkScript(World* world, const int x, const int y) :
  Component(TICK_GROUP_DEFAULT, TICK_TYPE_NOT_TICKABLE, true),
  WORLD_OFFSET_X((float)(x * world->TOTAL_CHUNK_SIZE)),
  WORLD_OFFSET_Y((float)(y * world->TOTAL_CHUNK_SIZE)),
  VP_OFFSET_X(
    Window::worldToViewportCoords((float)(x * world->TOTAL_CHUNK_SIZE))
  ),
  VP_OFFSET_Y(
    Window::worldToViewportCoords((float)(y * world->TOTAL_CHUNK_SIZE))
  )
{
  this->world = world;

  ////create rows
  table.resize(world->CHUNK_SIZE);

  //fill rows
  for (uint i=0; i< world->CHUNK_SIZE; i++)
  {
    table[i].resize(world->CHUNK_SIZE);
  }
}

void ChunkScript::onCreate()
{
  world->addRigidBody(new RigidBody2D(true));
}

void ChunkScript::onRender() const
{
  Shader* shader = Resources::getDefaultShader();
  uint id;
  Tile* tile;
  shader->use();

  float vpTileSize = Window::worldToViewportCoords((float)world->TILE_SIZE);

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
            VP_OFFSET_X + (float)(x * vpTileSize),
            VP_OFFSET_Y - (float)(y * vpTileSize),
            shader
          );
        }
      }
    }
  }
}