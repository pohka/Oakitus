#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <map>
#include <string>
#include <core/types.h>

namespace oak
{
  namespace ui
  {
    struct Localization
    {
      static std::map<uint, std::string> strings;
      static void addString(const uint id, std::string value);
    };
  }
}

#endif