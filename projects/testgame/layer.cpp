#include "layer.h"

using namespace game;

Layer::Layer(std::string name, int map[CHUNK_SIZE][CHUNK_SIZE])
{
  this->name = name;

  for (unsigned int y = 0; y < CHUNK_SIZE; y++)
  {
    for (unsigned int x = 0; x < CHUNK_SIZE; x++)
    {
      this->map[y][x] = map[y][x];
    }
  }
}

Layer::~Layer()
{

}

std::string Layer::getName()
{
  return name;
}