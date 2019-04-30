#include <oak/localization/localization.h>
#include <oak/debug.h>
#include <oak/localization/lsd_parser.h>
#include <oak/localization/lsd_validator.h>

using namespace ion;

std::vector<std::string> Localization::languageOptions;
unsigned int Localization::languageID = 0;
std::map<std::string, std::string> Localization::strings;

void Localization::init(const std::string& defaultLang)
{
  languageOptions.push_back(defaultLang);
  loadStrings(defaultLang);
}

void Localization::addLanguageOption(const std::string& langName)
{
  languageOptions.push_back(langName);
}

void Localization::setLanguage(const std::string& langName)
{
  //current language is already set
  if (langName == getLanguage())
  {
    return;
  }

  //check if language option exists
  bool isFound = false;
  for (unsigned int i=0; i<languageOptions.size() && !isFound; i++)
  {
    if (languageOptions[i] == langName)
    {
      languageID = i;
      isFound = true;
    }
  }

  if (!isFound)
  {
    LOG_WARNING << "No language option found for: '" << langName << "'";
  }
  else
  {
    loadStrings(langName);
  }
}

const std::string& Localization::getLanguage()
{
  return languageOptions[languageID];
}


void Localization::setString(const std::string& key, const std::string& value)
{
  strings[key] = value;
}

const std::string& Localization::getString(const std::string& key)
{
  auto it = strings.find(key);
  if (it == strings.end())
  {
    LOG_WARNING << "localization string key does not exist";
    return "#" + key;
  }
  return it->second;
}

void Localization::loadStrings(const std::string& name)
{
  std::string path = "strings/" + name + ".lsd";

#ifdef DEBUG_MODE
  LSDValidator::validate(path);
#endif

  LSDParser parser = LSDParser();
  if (parser.load(path))
  {
    strings = parser.getData();
  }
  else
  {
    LOG_WARNING << "Localization file could not be loaded: " << path;
  }
}