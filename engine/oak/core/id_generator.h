#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include "types.h"

namespace oak
{
  ///<summary>ID generator using an auto incrementer uint</summary>
  class IDGenerator
  {
    uint count;

    public:
      IDGenerator();
      ~IDGenerator();
      uint nextID();
  };
}
#endif
