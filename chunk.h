#ifndef CHUNK_H
#define CHUNK_H

#include <string>
#include <vector>
#include "layer.h"
#include "tile.h"



namespace game
{
  class Chunk
  {
    int x;
    int y;
    std::vector<Layer> layers;

    public:
      Chunk(int x, int y, std::vector<Layer> layers);
      ~Chunk();

      Layer* findLayerByName(std::string layerName);
      void drawLayer(std::string layerName, std::vector<Tile*> tiles, float screenH);
      Tile* findTileByID(std::vector<Tile*> tiles, int id);
      int chunkTotalSize();
  };
}

#endif