#ifndef CHUNK_H
#define CHUNK_H

#include <string>
#include <vector>



namespace game
{
  const int CHUNK_SIZE = 32;

  struct Layer
  {
    std::string name;
    std::vector<std::vector<int>> map;
  };

  struct Chunk
  {
    int x;
    int y;
    std::vector<Layer> layers;
  };
}

#endif