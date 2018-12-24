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
      static cnum STATE_ATTR_KEY = 1;
      static cnum STATE_ATTR_VALUE = 2;

      static void parse(std::string path);

      static bool parseSelectors(
        std::string& text, 
        std::vector<std::string>& strs
      );

      

      static std::vector<std::string> loadedFiles;


  };
}

#endif