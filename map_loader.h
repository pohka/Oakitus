#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "oak/xml/xml_node.h"
#include "tile.h"
#include <string>
#include "chunk.h"

namespace game
{
  class MapLoader
  {
  public:
    static void loadMap(std::string path);

  private:
    static std::vector<Tile> traverseTiles(XMLNode* rootTileNode);
    static std::vector<Chunk> traverseChunks(XMLNode* rootChunkNode);
    static std::vector<Layer> traverseLayers(XMLNode* rootLayerNode);
    static std::vector<std::string> traverseList(XMLNode* parentNode);
    static std::vector<int> splitRowStr(std::string strToSplit);
  };
}
#endif