#ifndef META_DATA_H
#define META_DATA_H

#include <map>
#include <nlohmann/json.hpp>
#include <oak/core/types.h>

namespace oak
{
  static uchar META_DATA_KEY_SCENE = 0;
  static uchar META_DATA_KEY_ABILITYS = 1;
  
  static const char ARG_NUMBER = 1;
  static const char ARG_INT = 2;
  static const char ARG_UINT = 3;
  static const char ARG_STRING = 4;
  static const char ARG_BOOLEAN = 5;
  static const char ARG_ARRAY_OBJ = 6;

  class MetaData
  {
    static std::map<uchar, nlohmann::json> dataMap;

  public:
    //argument types


    static std::string projectPath;

    static void load(uchar type, const std::string& fileName);
    static const nlohmann::json& getData(uchar type);
  };
}

#endif