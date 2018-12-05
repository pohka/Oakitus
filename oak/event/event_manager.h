#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H

#include "../core/types.h"
#include <vector>
#include <unordered_map>
#include "event_listener.h"
#include "base_event.h"

namespace oak
{
  

  class EventManager
  {
    static std::vector<BaseEvent*> eventList;
    
    public:
      static void addEvent(BaseEvent* event);
      static BaseEvent* getEventByID(uchar id);
      static void addListener(uchar eventID, EventListener* listener);
  };


  template <typename Event, typename Data>
  void fireEvent(uchar eventID, Data& data)
  {
    BaseEvent* evt = EventManager::getEventByID(eventID);
    static_cast<Event*>(evt)->fire(data);
  }
}
#endif
