#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <vector>
#include "event.h"
#include <debug.h>

namespace oak
{
  class EventManager
  {
    static std::vector<IEvent*> events;

    public :
      static void addEvent(IEvent* event)
      {
        events.push_back(event);
      }

      static IEvent* getEvent(uchar id)
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

  template <typename mEvent, typename Listener>
  void addEventListener(uchar eventType, Listener* listener)
  {
    oak::IEvent* event = oak::EventManager::getEvent(eventType);
    mEvent* customEvent = static_cast<mEvent*>(event);
    customEvent->addListener(listener);
  }
}

#endif