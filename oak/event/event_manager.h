#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <vector>
#include "event.h"

namespace oak
{
  class EventManager
  {
    static std::vector<Event*> events;

    public :
      static void addEvent(Event* event)
      {
        events.push_back(event);
      }

      static Event* getEvent(uchar id)
      {
        for (uint i = 0; i < events.size(); i++)
        {
          if (events[i]->getID() == id)
          {
            return events[i];
          }
        }

        return nullptr;
      }
  };
}

#endif