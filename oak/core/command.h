#ifndef COMMAND_H
#define COMMAND_H

namespace oak
{
  class Command
  {
  public:
    virtual void execute() = 0;
  };
}

#endif