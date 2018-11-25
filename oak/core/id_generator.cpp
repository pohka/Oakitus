#include "id_generator.h"
#include <limits.h>

using namespace oak;

IDGenerator::IDGenerator()
{
  this->count = 1;
}

IDGenerator::~IDGenerator()
{
 
}

uint IDGenerator::nextID()
{
  uint id = count;
  if (count == UINT_MAX)
  {
    count = 0;
  }
  else
  {
    count++;
  }
  return id;
}