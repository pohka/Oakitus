#include <oak/core/config.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <oak/debug.h>

using namespace oak;


nlohmann::json Config::data;

unsigned int Config::getUInt(const std::string& key, unsigned int defaultVal)
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


std::string Config::getString(const std::string& key, const std::string& defaultVal)
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

bool Config::getBool(const std::string& key, bool defaultVal)
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
void Config::load()
{
  std::ifstream i("config.json");
  if (i.fail())
  {
    LOG_ERROR << "failed to load config file";
  }
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
