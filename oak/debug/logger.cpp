#include "logger.h"

using namespace debug;

std::vector<Logger::Timer> Logger::timers;
LogData Logger::lastLog = {"", "", 0, 0};
uint Logger::logRepeatCount = 0;
bool Logger::hasReachedMaxRepeats = false;

Logger::Logger(
  const std::string &funcName, 
  const std::string &file, 
  int line, 
  uchar logType
)
{
  if (isRepeatedLog(funcName, file, line, logType))
  {
    if (logRepeatCount < MAX_REPEATED_LOGS)
    {
      logRepeatCount++;
    }
    if (logRepeatCount == MAX_REPEATED_LOGS)
    {
      std::cout << "REPEATED LOGS WILL NOT BE SHOWN";
      logRepeatCount++;
      hasReachedMaxRepeats = true;
    }
  }
  else
  {
    logRepeatCount = 0;
    hasReachedMaxRepeats = false;
  }

  if (!hasReachedMaxRepeats)
  {
    this->logType = logType;
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

    lastLog.funcName = funcName;
    lastLog.file = file;
    lastLog.line = line;
    lastLog.logType = logType;
  }
}

Logger::~Logger()
{
  if (!hasReachedMaxRepeats)
  {
    std::cout << std::endl;
    //pause if error logged
    if (logType == DEBUG_LOG_ERROR)
    {
      system("Pause");
    }
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

bool Logger::isRepeatedLog(
  const std::string &funcName,
  const std::string &file,
  int line,
  uchar logType
)
{
  return (
    lastLog.file == file &&
    lastLog.funcName == funcName &&
    lastLog.line == line &&
    lastLog.logType == logType
  );
}