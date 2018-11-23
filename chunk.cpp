#include "chunk.h"
#include "oak/core/types.h"

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

int Chunk::chunkTotalSize()
{
  return 16 * 32;
}

Tile* Chunk::findTileByID(std::vector<Tile*> tiles, int id)
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

void Chunk::drawLayer(std::string layerName, std::vector<Tile*> tiles, float screenH)
{
  int tileSize = 16;
  if (true || x == 0 && y == 0)
  {
    Layer* layer = findLayerByName(layerName);

    //convert from chunk to world coords
    int chunkOffsetX = x * chunkTotalSize();
    int chunkOffsetY = y * chunkTotalSize();


    //draw all tiles in chunk
    for (uint y = 0; y < CHUNK_SIZE; y++)
    {
      for (uint x = 0; x < CHUNK_SIZE; x++)
      {
        int tileID = layer->map[y][x];
        if (tileID > -1)
        {
          Tile* tile = findTileByID(tiles, tileID);

          int tileOffsetX = x * tileSize;
          int tileOffsetY = y * tileSize;
          float vpPosX = (float)(tileOffsetX + chunkOffsetX) / screenH;
          float vpPosY = (float)(-tileOffsetY + chunkOffsetY) / screenH;
          tile->onDraw(vpPosX, vpPosY);
        }
      }
    }
  }
}