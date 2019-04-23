#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <nlohmann/json.hpp>
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
      static unsigned int getUInt(const std::string key, const unsigned int defaultVal);

      //get string value from config
      //if key-value is not found then the default value is returned
      static std::string getString(const std::string key, const std::string defaultVal);

      //get bool value from config
      //if key-value is not found then the default value is returned
      static bool getBool(const std::string key, const bool defaultVal);

      //load the config file
      static void load();
  };
}

#endif