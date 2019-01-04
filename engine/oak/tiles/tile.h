#ifndef TILE_TILE_H
#define TILE_TILE_H

#include <oak/core/types.h>
#include <oak/assets/texture.h>

namespace tile
{
  struct Tile
  {
    const uint tileID;
    const uint textureID;
    const uint shaderID;
    uint VAO;
    uint VBO;

    Tile(
      const uint tileID,
      const oak::Texture* texture,
      const uint TEX_COORD_X,
      const uint TEX_COORD_Y,
      const uint shaderID,
      const uint TILE_SIZE
    );

    ~Tile();

    void onRender(const float x, const float y) const;
  };
}

#endif
