#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include "time.h"

namespace oak
{
  class Debug
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
      Debug();
      //LOG_ERROR and LOG_WARNING
      Debug(
        const std::string &funcName, 
        const std::string &file, 
        int line, 
        bool isError
      );
      ~Debug();

      static void startTimer(std::string name, std::string msg);
      static void endTimer(std::string name);

      //print the next value
      template <class T>
      Debug &operator<<(const T &v)
      {
        std::cout << v;
        return *this;
      }
  };

  
}


#define LOG_ERROR Debug(__FUNCTION__, __FILE__, __LINE__, true)
#define LOG_WARNING Debug(__FUNCTION__, __FILE__, __LINE__, false)
#define LOG Debug()

#endif