#ifndef WORLD_H
#define WORLD_H

#include "chunk.h"
#include "tile.h"
#include <vector>
#include "oak/core/entity.h"

namespace game
{
  class World : public oak::Entity
  {
    std::vector<Chunk> chunks;
    std::vector<Tile*> tiles;
    std::vector<std::string> layerOrder;
    int chunkSize;
    int tileSize;
    unsigned int VBO, VAO;
    int shaderID;

    public:
      World(
        std::vector<Chunk> chunks,
        std::vector<Tile*> tiles,
        std::vector<std::string> layerOrder,
        int chunkSize,
        int tileSize
      );
      ~World();

      //void onDestroy();
      void onDraw() override;
     // void onUpdate() override;

    private:
      Tile* findTileByID(int id);
  };
}
#endif