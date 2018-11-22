#include "oak/oak.h"
#include "world.h"


#include <iostream>

using namespace game;
using namespace oak;

World::World(
  std::vector<Chunk> chunks,
  std::vector<Tile*> tiles,
  std::vector<std::string> layerOrder,
  int chunkSize,
  int tileSize
) {
  //std::cout << "chunks:" << chunks.size();
  this->chunks = chunks;
  this->tiles = tiles;
  this->layerOrder = layerOrder;
  this->chunkSize = chunkSize;
  this->tileSize = tileSize;

  this->shaderID = Resources::defaultShaderID;
}
World::~World()
{

}


void World::onDraw()
{
  for (uint i = 0; i < chunks.size(); i++)
  {
    
    //draw chunk 0,0
    if (chunks[i].x == 0 && chunks[i].y == 0)
    {
      
      Layer* layer = chunks[i].findLayerByName("ground");
      

      for (uint y = 0; y < CHUNK_SIZE; y++)
      {
        for (uint x = 0; x < CHUNK_SIZE; x++)
        {
          int tileID = layer->map[y][x];
          if (tileID > -1)
          {
            Tile* tile = findTileByID(tileID);
            tile->onDraw(x, y);
          }
        }
      }
    }
  }
}

Tile* World::findTileByID(int id)
{
  if (id == -1) {
    return nullptr;
  }
  for (uint i = 0; i < tiles.size(); i++)
  {
    if (tiles[i]->id == id)
    {
      return tiles[i];
    }
  }
  return nullptr;
}
