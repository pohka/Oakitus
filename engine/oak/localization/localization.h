#pragma once
#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <map>
#include <string>
#include <vector>

namespace ion
{

  class Localization
  {
    static std::vector<std::string> languageOptions;
    static unsigned int languageID;
    static std::map<std::string, std::string> strings;

  public:
    static void init(const std::string& defaultLang);

    //add a language option, must be an all lowercase string
    static void addLanguageOption(const std::string& langName);

    //set the current language by name (name should be all lowercase)
    static void setLanguage(const std::string& langName);

    //get current language name
    static const std::string& getLanguage();

    //set a string value
    static void setString(const std::string& key, const std::string& value);

    //get a string valu
    static const std::string& getString(const std::string& key);

  private:
    static void loadStrings(const std::string& name);
  };
}

#endif