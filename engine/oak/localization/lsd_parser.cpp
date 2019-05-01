#include <oak/localization/lsd_parser.h>
#include <fstream>

using namespace oak;

bool LSDParser::load(const std::string& path)
{
  std::ifstream ifs(path);

  if (ifs.is_open())
  {
    std::string line;
    errorCode = ERROR_NONE;
    std::string key = "";
    std::string value = "";
    
    State state = State::NONE;
    bool isSpace = false;
    bool isEscaped = false;
    bool lastValueChWasSpace = true;

    while (getline(ifs, line))
    {
      if (line.length() > 0)
      {
        //commented line
        if (line[0] != TOKEN_COMMENT)
        {
          key.clear();
          value.clear();
          state = State::NONE;
          isEscaped = false;
          lastValueChWasSpace = true;

          for (const char c : line)
          {
            isSpace = isspace(c);
            switch (state)
            {
              case State::NONE:
              {
                if (!isSpace)
                {
                  key += c;
                  state = State::KEY;
                }
              }
              break;
              case State::KEY :
              {
                if (isSpace || c == TOKEN_EQUALS)
                {
                  state = State::BETWEEN;
                }
                else
                {
                  key += c;
                }
              }
              break;
              case State::BETWEEN :
              {
                if (c == TOKEN_QUOTE)
                {
                  state = State::VALUE;
                }
              }
              break;
              case State::VALUE :
              {
                if (c == TOKEN_QUOTE && !isEscaped)
                {
                  //if last character is space
                  if (value.length() > 0 && isspace(value.back()))
                  {
                    value.pop_back();
                  }

                  data[key] = value;
                  state = State::NONE;
                }
                else
                {
                  if ((!lastValueChWasSpace && isSpace) || !isSpace)
                  {
                    value += c;
                  }
                  lastValueChWasSpace = isSpace;
                }
              }
              break;
            }

            isEscaped = (c == TOKEN_ESCAPE);
          }
        }
      }
    }
  }
  else
  {
    //error opening file
    errorCode = ERROR_FILE_NOT_OPENED;
  }


  ifs.close();
  return errorCode == ERROR_NONE;
}

void LSDParser::clear()
{
  data.clear();
}

const std::map<std::string, std::string>& LSDParser::getData() const
{
  return data;
}
