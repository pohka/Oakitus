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

    private:
      static cnum STATE_CLASSNAME = 0;
      static cnum STATE_ATTRIBUTES = 1;

      static bool parseClassNames(
        std::string& text, 
        std::vector<std::string>& strs
      );

      static bool parseAttr(
        std::string& line, 
        std::pair<std::string, std::string>& kv, 
        unsigned int lineNum
      );

  };
}

#endif