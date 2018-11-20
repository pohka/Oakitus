#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "oak/xml/xml_node.h"
#include "tile.h"
#include <string>

namespace game
{
  class MapLoader
  {
  public:
    static void loadMap(std::string path);

  private:
    static std::vector<Tile> traverseTiles(XMLNode* rootTileNode);
  };
}
#endif