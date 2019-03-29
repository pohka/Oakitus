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
#ifdef DEBUG_MODE
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
    output += " |";

    //|--WARNING--| and |--ERROR--|
    if (logType == DEBUG_LOG_WARNING)
    {
      output += "--WARNING--|";
    }
    else if (logType == DEBUG_LOG_ERROR)
    {
      output += "--ERROR--|";
    }
    //else if (logType == DEBUG_LOG_LUA_ERROR)
    //{
    //  output += "--LUA ERROR--|";
    //}

    std::cout <<  output + " ";

    lastLog.funcName = funcName;
    lastLog.file = file;
    lastLog.line = line;
    lastLog.logType = logType;
  }
#endif;
}

Logger::~Logger()
{
#ifdef DEBUG_MODE
  if (!hasReachedMaxRepeats)
  {
    std::cout << std::endl;
    //pause if error logged
    if (logType == DEBUG_LOG_ERROR)
    {
      system("Pause");
    }
  }
#endif
}

void Logger::startTimer(std::string name, std::string msg)
{
#ifdef DEBUG_MODE
  Timer t;
  t.name = name;
  t.startTime = oak::Time::getGameTime();
  t.msg = msg;

  timers.push_back(t);
#endif
}

void Logger::endTimer(std::string name)
{
#ifdef DEBUG_MODE
  for (unsigned int i = 0; i < timers.size(); i++)
  {
    if (timers[i].name == name)
    {
      float diff = oak::Time::getGameTime() - timers[i].startTime;
      std::cout << std::fixed << std::setprecision(2) << diff << "s : " << timers[i].msg << std::endl;
      timers.erase(timers.begin() + i);
    }
  }
#endif
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