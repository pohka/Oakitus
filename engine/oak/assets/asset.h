#pragma once
#ifndef ASSET_H
#define ASSET_H

#include <string>

namespace oak
{
  struct Asset
  {
    friend struct Meta;
    Asset(const std::string& name, bool isEngineAsset);

    bool getIsEngineAsset() const;
    std::string getName() const;
    unsigned int getID() const;
    
  protected:
    std::string name;
    bool isEngineAsset;
    unsigned int id;
    
  };
}

#endif