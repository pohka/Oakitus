#ifndef STRING_HELP_H
#define STRING_HELP_H

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

namespace oak
{
  struct StringHelp
  {
    //splits string
    static void split(const std::string &txt, std::vector<std::string> &strs, char ch)
    {
      unsigned int pos = txt.find(ch);
      unsigned int initialPos = 0;
      strs.clear();

      // Decompose statement
      while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
      }

      // Add the last one
      strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));
    }

    //remove all occurances of a character in the string
    static void removeChar(std::string& str, char c)
    {
      str.erase(remove(str.begin(), str.end(), c), str.end());
    }

    //returns true if the string is valid a decimal number
    static bool isNumber(std::string s)
    {
      bool decimalPt = false;
      auto it = s.begin();
      for(; it != s.end(); it++)
      {
        if (!std::isdigit(*it))
        {
          if (*it == '.' && !decimalPt)
          {
            decimalPt = true;
          }
          else
          {
            return false;
          }
        }
      }
      return true;
    }
  };
}

#endif