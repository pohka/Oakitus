#include "oak/oak.h"
#include "map_loader.h"

#include <vector>
#include "oak/xml/xml_parser.h"
#include <iomanip>

using namespace game;
using namespace oak;

World* MapLoader::loadMap(std::string path)
{
  double startTime = glfwGetTime();
  XMLNode root = XMLParser::load(path);
  std::cout << "File Loaded: " << std::fixed << std::setprecision(2) << (glfwGetTime() - startTime) << "s" << std::endl;

  double parseStartTime = glfwGetTime();

  XMLNode* worldNode = root.getChildNodes()[0];
  std::vector<XMLNode*> nodes = worldNode->getChildNodes();

  std::vector<Tile*> tiles;
  std::vector<Chunk> chunks;
  std::vector<std::string> layerOrder;
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
      chunks = traverseChunks(nodes[i]);
    }
    else if (nodes[i]->name == "layerOrder")
    {
      layerOrder = traverseList(nodes[i]);
    }
  }


  std::cout << "File Parsed: " << std::fixed << std::setprecision(2) << (glfwGetTime() - parseStartTime) << "s" << std::endl;

  return new World(chunks, tiles, layerOrder, chunkSize, tileSize);
}

std::vector<Tile*> MapLoader::traverseTiles(XMLNode* rootTileNode)
{
  std::vector<Tile*> tiles;
  std::vector<XMLNode*> tileNodes = rootTileNode->getChildNodes();
  //iterate through each tile
  for (uint a = 0; a < tileNodes.size(); a++)
  {
    std::vector<XMLNode*>tileParamNodes = tileNodes[a]->getChildNodes();

    std::string src;
    int x, y, id;
    Tile::Collision collision;
    //read params for tile
    for (uint b = 0; b < tileParamNodes.size(); b++)
    {
      if (tileParamNodes[b]->name == "src")
      {
        src = tileParamNodes[b]->content;
      }
      else if (tileParamNodes[b]->name == "x")
      {
        x = std::stoi(tileParamNodes[b]->content);
      }
      else if (tileParamNodes[b]->name == "y")
      {
        y = std::stoi(tileParamNodes[b]->content);
      }
      else if (tileParamNodes[b]->name == "collision")
      {
        collision = Tile::Collision(std::stoi(tileParamNodes[b]->content));
      }
      else if (tileParamNodes[b]->name == "id")
      {
        id = std::stoi(tileParamNodes[b]->content);
      }
    }
    tiles.push_back(new Tile(x, y, src, collision, id));
  }
  return tiles;
}

std::vector<Chunk> MapLoader::traverseChunks(XMLNode* rootChunkNode)
{
  std::vector<Chunk> chunks;
  

  std::vector<XMLNode*> chunkNodes = rootChunkNode->getChildNodes();

  //iterate through each chunk
  for (uint i = 0; i < chunkNodes.size(); i++)
  {
    Chunk chunk;
    std::vector<XMLNode*> chunkParamNodes = chunkNodes[i]->getChildNodes();
    for (uint a = 0; a < chunkParamNodes.size(); a++)
    {
      if (chunkParamNodes[a]->name == "x")
      {
        chunk.x = std::stoi(chunkParamNodes[a]->content);
      }
      else if (chunkParamNodes[a]->name == "y")
      {
        chunk.y = std::stoi(chunkParamNodes[a]->content);
      }
      else if(chunkParamNodes[a]->name == "layers")
      {
        chunk.layers = traverseLayers(chunkParamNodes[a]);
      }
    }
    chunks.push_back(chunk);
  }

  return chunks;
}

std::vector<int> MapLoader::splitRowStr(std::string strToSplit)
{
  const char delimeter = ',';
  std::stringstream ss(strToSplit);
  std::string id;
  std::vector<int> row;
  while (std::getline(ss, id, delimeter))
  {
    row.push_back(std::stoi(id));
  }
  return row;
}

std::vector<Layer> MapLoader::traverseLayers(XMLNode* rootLayerNode)
{
  std::vector<Layer> layers;
  std::vector<XMLNode*> layerNodes = rootLayerNode->getChildNodes();
  
  for (uint i = 0; i < layerNodes.size(); i++)
  {
    std::string layerName;

    int arr[CHUNK_SIZE][CHUNK_SIZE] = { {-1} };
    std::vector<XMLNode*> layerParamNodes = layerNodes[i]->getChildNodes();
    for (uint a = 0; a < layerParamNodes.size(); a++)
    {
      std::string paramName = layerParamNodes[a]->name;
      if (paramName == "name")
      {
        layerName = layerParamNodes[i]->content;
      }
      else if(paramName =="map")
      {
        std::vector<XMLNode*> rowNodes = layerParamNodes[a]->getChildNodes();
        
        for (uint r = 0; r < rowNodes.size(); r++)
        {
          std::vector<int> row = splitRowStr(rowNodes[r]->content);
          for (uint c = 0; c < row.size(); c++)
          {
            arr[r][c] = row[c];
          }
          
        }
      }
    }
    layers.push_back(*new Layer(layerName, arr));
  }

  return layers;
}

std::vector<std::string> MapLoader::traverseList(XMLNode* parentNode)
{
  std::vector<XMLNode*> nodes = parentNode->getChildNodes();
  std::vector<std::string> values;
  for (uint i = 0; i < nodes.size(); i++)
  {
    values.push_back(nodes[i]->content);
  }

  return values;
}