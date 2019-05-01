#include <oak/localization/localization.h>
#include <oak/debug.h>
#include <oak/localization/lsd_parser.h>
#include <oak/localization/lsd_validator.h>

using namespace oak;

void Localization::init(std::string langID, const std::string& langNativeName)
{
  addLangSupport(langID, langNativeName);
  setLanguage(langID);
}

//sets the language and loaded it from file
void Localization::setLanguage(std::string langID)
{
  //current language is already set
  if (langID == getCurrentLangID())
  {
    return;
  }

  //check if language option exists
  const std::vector<Lang>& langOptions = getLangOptions();
  std::string nativeName = "";
  bool isFound = false;
  for (unsigned int i=0; i< langOptions.size() && !isFound; i++)
  {
    if (langOptions[i].id == langID)
    {
      nativeName = langOptions[i].nativeName;
      isFound = true;
    }
  }

  if (!isFound)
  {
    LOG_WARNING << "No language option found for langID: '" << langID << "'";
  }
  else
  {
    loadStrings(nativeName);
  }
}

void Localization::set(const std::string& key, const std::string& value)
{
  strings[key] = value;
}

const std::string& Localization::get(const std::string& key)
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

