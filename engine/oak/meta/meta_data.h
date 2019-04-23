#ifndef META_DATA_H
#define META_DATA_H

#include <map>
#include <nlohmann/json.hpp>
#include <oak/core/types.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace oak
{
  //dataMap keys
  static uchar META_DATA_KEY_SCENE = 0;
  static uchar META_DATA_KEY_ABILITYS = 1;
  
  //argument types
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
    static std::string projectPath;

    //loads json metadata from file
    static void load(uchar key, const std::string& fileName);

    //get loaded data by key
    static const nlohmann::json& getData(uchar key);

    static std::vector<float> parseArrayString(const std::string& value)
    {
      std::istringstream iss(value);
      std::vector<std::string> results(
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>());

      std::vector<float> resultF;
      for (std::string& str : results)
      {
        resultF.push_back(stof(str));
      }
      return resultF;
    }
  };
}

#endif