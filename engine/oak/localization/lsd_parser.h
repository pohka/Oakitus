#pragma once
#ifndef LSD_PARSER_H
#define LSD_PARSER_H

#include <string>
#include <map>

/*
  Localization String Data
  --------------------------
  -key values of strings


  -the key must have no spaces
  -the value must be in quotes
  -excess spaces in value will be removed
  -spaces before and after value will be removed
  -empty lines and lines with only spaces are ignored

  -if parsing fails on a line, that line will be ignored
  -the parser will continue parsing the rest of the file and ignore the data on that line


  EXAMPLE:
  key = "My Value"
  mana  = "Mana"
  shop_1 = "Johnny's Shop"

  # commented line
  health = "Health"
  #this also works
  other="my value"
  shop_4 = "You can also do \n new lines"
  shop_3 = "you can escape using \"backslash\"   "

*/

namespace oak
{
  class LSDParser
  {
    std::map<std::string, std::string> data;
    unsigned char errorCode;

  public:
    friend class LSDValidator;

    bool load(const std::string& path);
    void clear();
    const std::map<std::string, std::string>& getData() const;

  private:
    enum class State : unsigned char
    {
      NONE,
      KEY,
      BETWEEN,
      VALUE,
      END
    };

    static const char TOKEN_COMMENT = '#';
    static const char TOKEN_QUOTE = '\"';
    static const char TOKEN_EQUALS = '=';
    static const char TOKEN_ESCAPE = '\\';

    static const char ERROR_NONE = 0;
    static const char ERROR_FILE_NOT_OPENED = 1;
  };
}

#endif
