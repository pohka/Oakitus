#ifndef WORLD_H
#define WORLD_H

#include "chunk.h"
#include "tile.h"
#include <vector>
#include "oak/core/entity.h"



namespace game
{
  class Chunk;

  class World : public oak::Entity
  {
    std::vector<Chunk> chunks;
    std::vector<Tile*> tiles;
    std::vector<std::string> layerOrder;
    
    int shaderID;
    int chunkSize; //number of tiles per chunk on one dimension
    int tileSize; //pixels of each tile
    int chunkTotalSize; //chunk pixel size

    public:
      World(
        std::vector<Chunk> chunks,
        std::vector<Tile*> tiles,
        std::vector<std::string> layerOrder,
        int chunkSize,
        int tileSize
      );
      ~World();
      int getChunkTotalSize();
      int getTileSize();
      int getChunkSize();

      //void onDestroy();
      void onDraw() override;
     // void onUpdate() override;

      Tile* findTileByID(int id);
  };
}
#endif