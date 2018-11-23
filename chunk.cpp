#include "chunk.h"
#include "oak/core/types.h"
#include "world.h"

using namespace game;
using namespace oak;

Chunk::Chunk(int x, int y, std::vector<Layer> layers)
{
  this->x = x;
  this->y = y;
  this->layers = layers;
}

Chunk::~Chunk()
{

}

Layer* Chunk::findLayerByName(std::string layerName)
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

void Chunk::drawLayer(std::string layerName, World* world, float screenH)
{
  Layer* layer = findLayerByName(layerName);

  //convert from chunk to world coords
  int chunkOffsetX = x * world->getChunkTotalSize();
  int chunkOffsetY = y * world->getChunkTotalSize();


  //draw all tiles in layer of this chunk
  for (uint y = 0; y < CHUNK_SIZE; y++)
  {
    for (uint x = 0; x < CHUNK_SIZE; x++)
    {
      int tileID = layer->map[y][x];
      if (tileID > -1)
      {
        Tile* tile = world->findTileByID(tileID);

        int tileOffsetX = x * world->getTileSize();
        int tileOffsetY = y * world->getTileSize();
        float vpPosX = (float)(tileOffsetX + chunkOffsetX) / screenH;
        float vpPosY = (float)(-tileOffsetY + chunkOffsetY) / screenH;
        tile->onDraw(vpPosX, vpPosY);
      }
    }
  }
}