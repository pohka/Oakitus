#pragma once
#ifndef I_LOCALIZATION_H
#define I_LOCALIZATION_H

#include <string>
#include <vector>
#include <oak/localization/lang.h>

namespace oak
{
  class ILocalization
  {
    std::vector<Lang> languageOptions;
    std::string currentLangID = "";

  public:
    virtual void init(std::string langID, const std::string& nativeName) = 0;

    virtual const std::string& get(const std::string& key) = 0;

    virtual void set(const std::string& key, const std::string& value) = 0;

    virtual void setLanguage(std::string langID) = 0;

    

    std::string getCurrentLangID() const
    {
      return currentLangID;
    }

    void addLangSupport(const std::string& langID, const std::string& nativeName)
    {
      languageOptions.push_back({ langID, nativeName });
    }

    const std::vector<Lang>& getLangOptions() const
    {
      return languageOptions;
    }
  };

}

#endif