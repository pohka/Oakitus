#ifndef SCRIPT_H
#define SCRIPT_H

#include "Types.h"

namespace oak
{
  class Entity;

  class Script
  {
    uint scriptID;

    friend class Entity;
    public:
      Script();
      virtual ~Script();
      virtual void onUpdate();
      virtual void init();


    protected:
      Entity* entity;

    };
}

#endif
