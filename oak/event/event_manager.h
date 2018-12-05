#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <vector>
#include "event.h"
#include <debug.h>

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
        LOG_WARNING << "Event not found with id:" << id;
        return nullptr;
      }
  };

  template <typename CustomEvent, typename Listener>
  void addEventListener(uchar eventType, Listener* listener)
  {
    oak::Event* event = oak::EventManager::getEvent(eventType);
    CustomEvent* customEvent = static_cast<CustomEvent*>(event);
    customEvent->addListener(listener);
  }
}

#endif