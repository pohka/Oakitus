#ifndef CHUNK_H
#define CHUNK_H

#include <string>
#include <vector>
#include "layer.h"



namespace game
{
  struct Chunk
  {
    int x;
    int y;
    std::vector<Layer> layers;

    Layer* findLayerByName(std::string layerName)
    {
      for (unsigned int i = 0; i < layers.size(); i++)
      {
        if (layers[i].getName().compare(layerName) == 0)
        {
          return &layers[i];
        }
      }

      return nullptr;
    }
  };
}

#endif