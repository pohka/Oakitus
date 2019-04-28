#pragma once
#ifndef PRECACHE_H
#define PRECACHE_H

#include <vector>
#include <string>
#include <limits>

namespace oak
{
  struct Precache
  {
    Precache() {}

    Precache(const Precache& p)
    {
      for (auto name : p.textures)
      {
        textures.push_back(name);
      }
      for (auto name : p.shaders)
      {
        shaders.push_back(name);
      }
      for (auto name : p.fonts)
      {
        fonts.push_back(name);
      }
    }

    std::vector<std::string> textures;
    std::vector<std::string> shaders;
    std::vector<std::string> fonts;

    static const unsigned int NULL_INDEX = std::numeric_limits<unsigned int>().max();

    unsigned int getIndex(const std::vector<std::string>& strs, const std::string& name) const
    {
      for (unsigned int i=0; i<strs.size(); i++)
      {
        if (strs[i] == name)
        {
          return i;
        }
      }

      return NULL_INDEX;
    }
  };
}

#endif