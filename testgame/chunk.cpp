#include "chunk.h"
#include "oak/core/types.h"
#include "world.h"
#include "oak/core/window.h"

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

void Chunk::drawLayer(std::string layerName, World& world)
{
  Layer* layer = findLayerByName(layerName);

  float screenH = (float)Window::getHeight();

  //convert from chunk to world coords
  int chunkOffsetX = x * world.getChunkTotalSize();
  int chunkOffsetY = y * world.getChunkTotalSize();


  //draw all tiles in layer of this chunk
  for (uint y = 0; y < CHUNK_SIZE; y++)
  {
    for (uint x = 0; x < CHUNK_SIZE; x++)
    {
      int tileID = layer->map[y][x];
      
      if (tileID > -1)
      {
        //performance: this is slow
        //should store tiles in ordered list rather than doing id comparisions
        Tile* tile = world.findTileByID(tileID);

        int tileOffsetX = x * world.getTileSize();
        int tileOffsetY = y * world.getTileSize();
        float posX = (float)(tileOffsetX + chunkOffsetX);
        float posY = (float)(-tileOffsetY + chunkOffsetY);
        float vpPosX = Window::worldToViewportCoords(posX);
        float vpPosY = Window::worldToViewportCoords(posY);
        tile->onDraw(vpPosX, vpPosY);
      }
    }
  }
}

int Chunk::getX()
{
  return x;
}

int Chunk::getY()
{
  return y;
}