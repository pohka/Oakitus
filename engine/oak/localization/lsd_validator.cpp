#include <oak/localization/lsd_validator.h>
#include <iostream>
#include <fstream>
#include <oak/localization/lsd_parser.h>
#include <vector>

using namespace ion;

bool LSDValidator::validate(const std::string& path)
{
  std::ifstream ifs(path);
  bool isSuccess = true;

  if (ifs.is_open())
  {
    std::string line;
    std::string key = "";
    std::string value = "";
    unsigned int lineNum = 0;

    LSDParser::State state = LSDParser::State::NONE;
    bool isSpace = false;
    bool isEscaped = false;
    bool lastValueChWasSpace = true;
    unsigned int lastExcessSpaceWarning = 0; //store last warning line to prevent repeated logs
    std::vector<std::string> keysUsed;

    while (getline(ifs, line))
    {
      lineNum++;

      if (line.length() > 0)
      {
        //commented line
        if (line[0] != LSDParser::TOKEN_COMMENT)
        {
          key.clear();
          value.clear();
          state = LSDParser::State::NONE;
          isEscaped = false;
          lastValueChWasSpace = true;

          for (const char c : line)
          {
            isSpace = isspace(c);
            switch (state)
            {
              case LSDParser::State::NONE:
              {
                if (!isSpace)
                {
                  key += c;
                  state = LSDParser::State::KEY;
                }
              }
              break;
              case LSDParser::State::KEY:
              {
                if (isSpace || c == LSDParser::TOKEN_EQUALS)
                {
                  state = LSDParser::State::BETWEEN;
                }
                else
                {
                  key += c;
                }
              }
              break;
              case LSDParser::State::BETWEEN:
              {
                if (c == LSDParser::TOKEN_QUOTE)
                {
                  state = LSDParser::State::VALUE;
                }
              }
              break;
              case LSDParser::State::VALUE:
              {
                if (c == LSDParser::TOKEN_QUOTE && !isEscaped)
                {
                  //if last character is space
                  if (value.length() > 0 && isspace(value.back()))
                  {
                    value.pop_back();
                    std::cout << "|--LSD WARNING--| Value has excess space at the end of line:" << std::to_string(lineNum) << std::endl;
                  }

                  if (key.length() == 0)
                  {
                    std::cout << "|--LSD WARNING--| Key has a length of zero, line:" << std::to_string(lineNum) << std::endl;
                  }
                  if (value.length() == 0)
                  {
                    std::cout << "|--LSD WARNING--| Value has a length of zero, line:" << std::to_string(lineNum) << std::endl;
                  }
                  //data[key] = value;
                  
                  bool isDupe = false;
                  for (unsigned int i = 0; i < keysUsed.size() && !isDupe; i++)
                  {
                    if (keysUsed[i] == key)
                    {
                      std::cout << "|--LSD WARNING--| Key has already been defined, line:" << std::to_string(lineNum) << std::endl;
                      isDupe = true;
                    }
                  }
                  if (!isDupe)
                  {
                    keysUsed.push_back(key);
                  }

                  state = LSDParser::State::NONE;
                }
                else
                {
                  if (lastValueChWasSpace && isSpace && lastExcessSpaceWarning != lineNum)
                  {
                    std::cout << "|--LSD WARNING--| Excessive spaces in value, line:" << std::to_string(lineNum) << std::endl;
                    lastExcessSpaceWarning = lineNum;
                  }
                  else if (!isSpace)
                  {
                    value += c;
                  }
                  lastValueChWasSpace = isSpace;
                }
              }
              break;
            }

            isEscaped = (c == LSDParser::TOKEN_ESCAPE);
          }

          if (state != LSDParser::State::NONE)
          {
            std::cout << "|--LSD WARNING--| Parsing error, line:" << std::to_string(lineNum) << std::endl;
          }
          
        }
      }
    }
  }
  else
  {
    //error opening file
    std::cout << "|--LSD_ERROR--| Failed to load file: '" << path << "'" << std::endl;
    isSuccess = false;
  }


  ifs.close();
  return isSuccess;
}
