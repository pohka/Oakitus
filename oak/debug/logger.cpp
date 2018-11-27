#include "logger.h"

using namespace debug;

std::vector<Logger::Timer> Logger::timers;

Logger::Logger()
{

}

//LOG_ERROR and LOG_WARNING
Logger::Logger(
  const std::string &funcName, 
  const std::string &file, 
  int line, 
  bool isError
)
{
  this->isError = isError;
  std::string output = "" + std::to_string(line);
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

Logger::~Logger()
{
  std::cout << std::endl;
  //pause if error logged
  if (isError)
  {
    system("Pause");
  }
}

void Logger::startTimer(std::string name, std::string msg)
{
  Timer t;
  t.name = name;
  t.startTime = oak::Time::getTimeNow();
  t.msg = msg;

  timers.push_back(t);
}

void Logger::endTimer(std::string name)
{
  for (unsigned int i = 0; i < timers.size(); i++)
  {
    if (timers[i].name == name)
    {
      float diff = oak::Time::getTimeNow() - timers[i].startTime;
      std::cout << std::fixed << std::setprecision(2) << diff << "s : " << timers[i].msg << std::endl;
      timers.erase(timers.begin() + i);
    }
  }
}