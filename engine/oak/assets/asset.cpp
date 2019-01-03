#include "asset.h"
#include "../oak_def.h"

using namespace oak;


Asset::Asset(const std::string& name, bool isEngineAsset)
{
  this->name = name;
  this->isEngineAsset = isEngineAsset;
}

bool Asset::getIsEngineAsset() const
{
  return isEngineAsset;
}

std::string Asset::getName() const
{
  return name;
}

unsigned Asset::getID() const
{
  return id;
}
