#ifndef STYLE_LOADER_H
#define STYLE_LOADER_H

#include <string>
#include <vector>
#include <core/types.h>

namespace ion
{
  class StyleLoader
  {
    public:
      static void load(std::string path);
      static void reload();

    private:
      static cnum STATE_CLASSNAME = 0;
      static cnum STATE_ATTRIBUTES = 1;

      static void parse(std::string path);

      static bool parseClassNames(
        std::string& text, 
        std::vector<std::string>& strs
      );

      static bool parseAttr(
        std::string& line, 
        std::pair<std::string, std::string>& kv, 
        unsigned int lineNum,
        std::string& path
      );

      static std::vector<std::string> loadedFiles;

      //returns true if valid css number
      static bool isValidNumber(const std::string& s);

  };
}

#endif