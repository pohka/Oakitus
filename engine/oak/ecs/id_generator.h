#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include <oak/core/types.h>

namespace oak
{
  ///<summary>ID generator using an auto incrementer uint</summary>
  struct IDGenerator
  {
    uint nextID()
    {
      count++;
      return count;
    }

    private:
      uint count = 0;
  };
}
#endif
