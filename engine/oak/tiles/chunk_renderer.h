#pragma once
#ifndef  CHUNK_RENDERER_H
#define  CHUNK_RENDERER_H

#include <oak/ecs/component.h>

namespace tile
{
  class Chunk;

  struct ChunkRenderer : oak::Component
  {
    //chunk offset in viewport coords
    const float VP_OFFSET_X;
    const float VP_OFFSET_Y;

    ChunkRenderer(Chunk* chunk);

    void onRender() const override;

  private:
  };
}

#endif
