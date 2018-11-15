#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

namespace oak
{
  class IDGenerator
  {
    unsigned int count;

    public:
      IDGenerator();
      ~IDGenerator();
      unsigned int nextID();
  };
}
#endif
