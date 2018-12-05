#ifndef EVENT_H
#define EVENT_H

#include "../core/types.h"
#include "event_data.h"

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

      virtual void fire(oak::EventData& data) = 0;
  };
}

#endif