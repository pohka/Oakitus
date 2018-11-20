#include "oak/oak.h"
#include "map_loader.h"

#include <vector>
#include "oak/xml/xml_parser.h"
#include <iomanip>

using namespace game;
using namespace oak;

void MapLoader::loadMap(std::string path)
{
  double startTime = glfwGetTime();
  XMLNode root = XMLParser::load(path);
  std::cout << "File Loaded: " << std::fixed << std::setprecision(2) << (glfwGetTime() - startTime) << "s" << std::endl;

  XMLNode* mapNode = root.getChildNodes()[0];
  std::vector<XMLNode*> nodes = mapNode->getChildNodes();
  std::cout << "child nodes:" << nodes.size() << std::endl;

  std::vector<Tile> tiles;
  int chunkSize;
  int tileSize;

  //traverse the map nodes
  for (uint i = 0; i < nodes.size(); i++)
  {
    //tiles
    if (nodes[i]->name == "tiles")
    {
      tiles = MapLoader::traverseTiles(nodes[i]);
    }
    else if (nodes[i]->name == "chunkSize")
    {
      chunkSize = std::stoi(nodes[i]->content);
    }
    else if (nodes[i]->name == "tileSize")
    {
      tileSize = std::stoi(nodes[i]->content);
    }
    else if (nodes[i]->name == "imgs")
    {

    }
    else if (nodes[i]->name == "chunks")
    {

    }
    else if (nodes[i]->name == "layerOrder")
    {

    }
  }

  std::cout << "tiles: " << tiles[1].id << std::endl <<
    "chunkSize:" << chunkSize << std::endl;

}

std::vector<Tile> MapLoader::traverseTiles(XMLNode* rootTileNode)
{
  std::vector<Tile> tiles;
  std::vector<XMLNode*> tileNodes = rootTileNode->getChildNodes();
  //iterate through each tile
  for (uint a = 0; a < tileNodes.size(); a++)
  {
    std::vector<XMLNode*>tileParamNodes = tileNodes[a]->getChildNodes();
    Tile tile;
    //read params for tile
    for (uint b = 0; b < tileParamNodes.size(); b++)
    {
      if (tileParamNodes[b]->name == "src")
      {
        tile.src = tileParamNodes[b]->content;
      }
      else if (tileParamNodes[b]->name == "x")
      {
        tile.srcX = std::stoi(tileParamNodes[b]->content);
      }
      else if (tileParamNodes[b]->name == "y")
      {
        tile.srcY = std::stoi(tileParamNodes[b]->content);
      }
      else if (tileParamNodes[b]->name == "collision")
      {
        tile.collision = Tile::Collision(std::stoi(tileParamNodes[b]->content));
      }
      else if (tileParamNodes[b]->name == "id")
      {
        tile.id = std::stoi(tileParamNodes[b]->content);
      }
    }
    tiles.push_back(tile);
  }
  return tiles;
}