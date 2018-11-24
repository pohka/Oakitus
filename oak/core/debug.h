#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iostream>

namespace oak
{
  class Debug
  {
    bool isError = false;
    public:
      //LOG
      Debug()
      {

      }

      //LOG_ERROR and LOG_WARNING
      Debug(const std::string &funcName, const std::string &file, int line, bool isError)
      {
        this->isError = isError;
        std::string output = ""+ std::to_string(line);
        //spacing between log
        while (output.length() < 3)
        {
          output += ' ';
        }
        output += "- " + funcName + "()";
        while (output.length() < 42)
        {
          output += ' ';
        }
        output += " | ";

        std::cout << output;
      }

      //print the next value
      template <class T>
      Debug &operator<<(const T &v)
      {
        std::cout << v;
        return *this;
      }

      ~Debug()
      {
        std::cout << std::endl;
        //pause if error logged
        if (isError)
        {
          system("Pause");
        }
      }
  };
}

#define LOG_ERROR Debug(__FUNCTION__, __FILE__, __LINE__, true)
#define LOG_WARNING Debug(__FUNCTION__, __FILE__, __LINE__, false)
#define LOG Debug()

#endif