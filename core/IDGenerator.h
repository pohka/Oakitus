#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include "Types.h"

namespace oak
{
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
