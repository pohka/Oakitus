#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <nlohmann/json.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <oak/debug.h>
#include <string>

namespace oak
{
  class Config
  {
    private:
      static nlohmann::json data;

    public:

      //get unsigned int value from config
      //if key-value is not found then the default value is returned
      static unsigned int getUInt(const std::string key, const unsigned int defaultVal)
      {
        if (data[key] != nullptr && data[key].is_number_unsigned())
        {
          return data[key];
        }
        else if (data[key] == nullptr)
        {
          LOG_WARNING << "config key not found '" << key << "'";
        }
        else
        {
          LOG_WARNING << "config key '" << key << "' is not an unsigned int";
        }
        return defaultVal;
      }

      //get string value from config
      //if key-value is not found then the default value is returned
      static std::string getString(const std::string key, const std::string defaultVal)
      {
        if (data[key] != nullptr && data[key].is_string())
        {
          return data[key];
        }
        else if (data[key] == nullptr)
        {
          LOG_WARNING << "config key not found '" << key << "'";
        }
        else
        {
          LOG_WARNING << "config key '" << key << "' is not a string";
        }
        return defaultVal;
      }

      //get bool value from config
      //if key-value is not found then the default value is returned
      static bool getBool(const std::string key, const bool defaultVal)
      {
        if (data[key] != nullptr && data[key].is_boolean())
        {
          return data[key];
        }
        else if (data[key] == nullptr)
        {
          LOG_WARNING << "config key not found '" << key << "'";
        }
        else
        {
          LOG_WARNING << "config key '" << key << "' is not a boolean";
        }
        return defaultVal;
      }

      //load the config file
      static void load()
      {
        std::ifstream i("../config.json");
        i >> data;
        if (data == nullptr)
        {
          //config not found
          LOG_ERROR << "config.json - file not found";
          return;
        }
        else if (data["project"] == nullptr)
        {
          LOG_ERROR << "config.json - 'project' key must be defined";
        }
      }
  };

  nlohmann::json Config::data;
}

#endif