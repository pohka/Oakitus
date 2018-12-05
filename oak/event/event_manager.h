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

      //template <class Listener, class Param>
      //static void fireEvent(uchar eventID, Param& param);

      //static void addListener(uchar eventID, EventListener* listener);

   // private:
      static BaseEvent* getEventByID(uchar id);
  };


  template <class Listener, class Param>
  void fireEvent(uchar eventID, Param& param)
  {
    BaseEvent* evt = EventManager::getEventByID(eventID);
    static_cast<Listener*>(evt)->fire(param);
  }
}
#endif
