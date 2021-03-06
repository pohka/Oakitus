#pragma once
#ifndef TILE_TILE_H
#define TILE_TILE_H

#include <oak/core/types.h>
#include <oak/assets/texture.h>
#include <oak/assets/shader.h>
#include <oak/collision/collision_rect.h>

namespace tile
{
  struct Tile
  {
    const uint tileID;
    const uint textureID;
    oak::CollisionRect collisionRect;

    Tile(
      const uint tileID,
      const oak::Texture* texture,
      const uint TEX_COORD_X,
      const uint TEX_COORD_Y,
      const uint TILE_SIZE,
      const uint spacing
    );


    ~Tile();

    void onRender(float vpX, float vpY, oak::Shader* shader) const;

  private:
    uint VAO;
    uint VBO;
  };
}

#endif
