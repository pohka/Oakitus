#include "debug.h"

using namespace oak;

std::vector<Debug::Timer> Debug::timers;

Debug::Debug()
{

}

//LOG_ERROR and LOG_WARNING
Debug::Debug(
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

Debug::~Debug()
{
  std::cout << std::endl;
  //pause if error logged
  if (isError)
  {
    system("Pause");
  }
}

void Debug::startTimer(std::string name, std::string msg)
{
  Timer t;
  t.name = name;
  t.startTime = Time::getTimeNow();
  t.msg = msg;

  timers.push_back(t);
}

void Debug::endTimer(std::string name)
{
  for (unsigned int i = 0; i < timers.size(); i++)
  {
    if (timers[i].name == name)
    {
      float diff = Time::getTimeNow() - timers[i].startTime;
      std::cout << std::fixed << std::setprecision(2) << diff << "s : " << timers[i].msg << std::endl;
      timers.erase(timers.begin() + i);
    }
  }
}