#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <vector>
#include "event.h"

namespace oak
{
  class EventManager
  {
    static std::vector<IEvent*> events;

    public :
      static void addEvent(IEvent* event);
      static IEvent* getEvent(uchar id);
  };

  template <typename mEvent, typename Listener>
  void addEventListener(uchar eventType, Listener* listener)
  {
    oak::IEvent* event = oak::EventManager::getEvent(eventType);
    mEvent* customEvent = static_cast<mEvent*>(event);
    customEvent->addListener(listener);
  }

  template <typename mEvent, typename Listener>
  void removeEventListener(uchar eventType, uint listenerID)
  {
    oak::IEvent* event = oak::EventManager::getEvent(eventType);
    mEvent* customEvent = static_cast<mEvent*>(event);
    customEvent->removeListener(listenerID);
    //customEvent->addListener(listener);
  }
}

#endif