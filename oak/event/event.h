#ifndef EVENT_H
#define EVENT_H

#include "../core/types.h"

namespace oak
{
  class Event
  {
    uchar id;

    public:
      Event(uchar id)
      {
        this->id = id;
      }

      uchar getID()
      {
        return id;
      }

     
  };
}

#endif