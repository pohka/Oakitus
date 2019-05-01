#pragma once
#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <map>
#include <string>
#include <oak/localization/i_localization.h>

namespace oak
{

  class Localization : public oak::ILocalization
  {
    std::map<std::string, std::string> strings;

  public:
    //initialize starting language
    void init(std::string langID, const std::string& langNativeName) override;

    //set the current language by name (name should be all lowercase)
    void setLanguage(std::string langID) override;

    //set a string value
    void set(const std::string& key, const std::string& value) override;

    //get a string value
    const std::string& get(const std::string& key) override;

  private:
    void loadStrings(const std::string& name);
  };
}

#endif