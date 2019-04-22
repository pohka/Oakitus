#include <oak/meta/meta_data.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <oak/debug.h>
#include <oak/meta/prefab_validator.h>

using namespace oak;

std::map<uchar, nlohmann::json> MetaData::dataMap;
std::string MetaData::projectPath = "";


void MetaData::load(uchar type, const std::string& fileName)
{
  std::string fullPath = projectPath + fileName;
  nlohmann::json data;
  std::ifstream i(fullPath);
  i >> data;
  i.close();

  if (data != nullptr)
  {
    LOG << "Meta data loaded: " << fullPath;
    dataMap[type] = data;
  }
  else
  {
    LOG_WARNING << "error loading meta data file: " << fullPath;
  }
}

const nlohmann::json& MetaData::getData(uchar type)
{
  return dataMap[type];
}

