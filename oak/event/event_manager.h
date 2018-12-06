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
      ///add an event
      static void addEvent(IEvent* event);
      ///get an event with a matching id
      static IEvent* getEvent(uchar id);
  };

  ///find the event by id and add the listener
  template <typename mEvent, typename Listener>
  void addEventListener(uchar eventID, Listener* listener)
  {
    oak::IEvent* event = oak::EventManager::getEvent(eventID);
    mEvent* customEvent = static_cast<mEvent*>(event);
    customEvent->addListener(listener);
  }

  ///find the event by id and remove the listener by id
  template <typename mEvent>
  void removeEventListener(uchar eventID, uint listenerID)
  {
    oak::IEvent* event = oak::EventManager::getEvent(eventID);
    mEvent* customEvent = static_cast<mEvent*>(event);
    customEvent->removeListener(listenerID);
  }
}

#endif