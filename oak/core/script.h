#ifndef SCRIPT_H
#define SCRIPT_H

#include "types.h"
#include "entity.h"

namespace oak
{
  class Entity;

  class Script
  {
    uint scriptID;
    

    friend class Entity;
    public:
      Script();
      virtual ~Script() = default;
      virtual void onStart();
      virtual void onUpdate();
      


    protected:
      Entity* entity;

    };
}

#endif
