#include "chunk.h"
#include <oak/collision/collision_rect.h>
#include "world.h"
#include "chunk_renderer.h"
#include <oak/components/rigid_body_2d.h>

using namespace tile;

Chunk::Chunk(int x, int y, const World* world) :
  oak::Entity(),
  CHUNK_X(x),
  CHUNK_Y(y)
{
  collisionLayer = oak::COLLISION_LAYER_WORLD;

  transform->moveTo(
    static_cast<float>(x * world->TOTAL_CHUNK_SIZE),
    static_cast<float>(y * world->TOTAL_CHUNK_SIZE),
    0.0f
  );

  //resize table
  table.resize(world->CHUNK_SIZE);
  for (uint i = 0; i < world->CHUNK_SIZE; i++)
  {
    table[i].resize(world->CHUNK_SIZE);
  }

  addComponent(new oak::RigidBody2D(true), true);
  addComponent(new ChunkRenderer(this));
}

World* Chunk::getWorld()
{
  return static_cast<World*>(parent);
}


void Chunk::genCollision()
{
  World* world = getWorld();
  float halfTile = static_cast<float>(world->TILE_SIZE / 2);

  for (uint y = 0; y < world->CHUNK_SIZE; y++)
  {
    for (uint x = 0; x < world->CHUNK_SIZE; x++)
    {
      uint tileID = table[y][x];
      if (tileID > 0)
      {
        addCollision(
          new oak::CollisionRect(
            transform->localPosition().x + static_cast<float>(x * world->TILE_SIZE) + halfTile,
            transform->localPosition().y - static_cast<float>(y * world->TILE_SIZE) - halfTile,
            static_cast<float>(world->TILE_SIZE),
            static_cast<float>(world->TILE_SIZE)
          )
        );
      }
    }
  }

  
}