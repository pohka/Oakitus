#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <map>
#include <string>
#include <core/types.h>

namespace ion
{
  struct Localization
  {
    static std::map<uint, std::string> strings;
    static void addString(const uint id, std::string value);
  };
}

#endif