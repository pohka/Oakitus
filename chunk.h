#ifndef CHUNK_H
#define CHUNK_H

#include <string>
#include <vector>
#include "layer.h"
#include "tile.h"
#include "world.h"


namespace game
{
  class World;

  class Chunk
  {
    int x;
    int y;
    std::vector<Layer> layers;

    public:
      Chunk(int x, int y, std::vector<Layer> layers);
      ~Chunk();

      Layer* findLayerByName(std::string layerName);
      void drawLayer(std::string layerName, World* world, float screenH);
  };
}

#endif