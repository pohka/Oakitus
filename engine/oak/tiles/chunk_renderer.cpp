#include "chunk_renderer.h"
#include "tile.h"
#include <oak/core/resources.h>
#include <oak/window/window.h>
#include "world.h"
#include "chunk.h"


using namespace tile;
using namespace oak;

ChunkRenderer::ChunkRenderer(Chunk* chunk) :
  Component(
    Reflect::CHUNK,
    Component::TickGroup::DEFAULT,
    TICK_TYPE_NOT_TICKABLE,
    true
  ),
  VP_OFFSET_X(Window::worldToViewportCoords(chunk->transform->localPosition().x)),
  VP_OFFSET_Y(Window::worldToViewportCoords(chunk->transform->localPosition().y))
{

}

void ChunkRenderer::onRender() const
{
  Chunk* chunk = static_cast<Chunk*>(entity);
  World* world = chunk->getWorld();
  Shader* shader = Resources::getDefaultShader();
  uint id;
  Tile* tile;
  shader->use();

  float vpTileSize = Window::worldToViewportCoords((float)world->TILE_SIZE);

  for (uint y = 0; y < chunk->table.size(); y++)
  {
    for (uint x = 0; x < chunk->table[y].size(); x++)
    {
      id = chunk->table[y][x];
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
