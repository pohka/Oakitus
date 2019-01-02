#ifndef PRECACHE_H
#define PRECACHE_H

#include <vector>
#include <string>

namespace oak
{
  struct Precache
  {
    std::vector<std::string> textures;
    std::vector<std::string> shaders;
    std::vector<std::string> fonts;
  };
}

#endif