#include "oak/oak.h"
#include "world.h"
#include "oak/core/window.h"
#include "bounds.h"

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

  this->chunks = chunks;
  this->tiles = tiles;
  this->layerOrder = layerOrder;
  this->chunkSize = chunkSize;
  this->tileSize = tileSize;
  this->chunkTotalSize = tileSize * chunkSize;

  std::cout << "layer orders: " << std::endl;
  for (uint i = 0; i < layerOrder.size(); i++)
  {
    std::cout << layerOrder[i] << std::endl;
  }
  std::cout << "---------" << std::endl;

  this->shaderID = Resources::defaultShaderID;
}

World::~World()
{

}

int World::getChunkTotalSize()
{
  return chunkTotalSize;
}

int World::getTileSize()
{
  return tileSize;
}
int World::getChunkSize()
{
  return chunkSize;
}


void World::onDraw()
{
  float screenH = (float)Window::getHeight();
  float cameraX = Store::camera->position.x;
  float cameraY = Store::camera->position.y;
  float windowWidth = (float)Window::getWidth();
  float windowHeight = (float)Window::getHeight();

  float halfW = windowWidth * 0.5f;
  float halfH = windowHeight * 0.5f;

  Bounds camBounds (
    cameraX - halfW,
    cameraY + halfH,
    windowWidth,
    windowHeight
  );


  float totalChunkSize = (float)getChunkTotalSize();

  int chunkCount = 0;
  for (uint i = 0; i < chunks.size(); i++)
  {
    Bounds chunkBounds (
      (float)chunks[i].getX() * totalChunkSize,
      (float)chunks[i].getY() * totalChunkSize,
      totalChunkSize,
      totalChunkSize
    );

    if (camBounds.intersects(chunkBounds))
    {
      //iterate layer order in reverse as the first index should be drawn last
      for (int a = layerOrder.size() - 1; a > -1; a--)
      {
        std::string layerName = layerOrder[a];
        chunks[i].drawLayer(layerName, *this);
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
