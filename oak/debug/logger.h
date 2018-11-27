#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <core/time.h>

namespace debug
{
  class Logger
  {
    bool isError = false;
    struct Timer
    {
      float startTime;
      std::string name;
      std::string msg;
    };
    
    static std::vector<Timer> timers;

    public:
      //LOG
      Logger();
      //LOG_ERROR and LOG_WARNING
      Logger(
        const std::string &funcName, 
        const std::string &file, 
        int line, 
        bool isError
      );
      ~Logger();

      static void startTimer(std::string name, std::string msg);
      static void endTimer(std::string name);

      //print the next value
      template <class T>
      Logger &operator<<(const T &v)
      {
        std::cout << v;
        return *this;
      }
  };

  
}


#define LOG_ERROR debug::Logger(__FUNCTION__, __FILE__, __LINE__, true)
#define LOG_WARNING debug::Logger(__FUNCTION__, __FILE__, __LINE__, false)
#define LOG debug::Logger()

#endif