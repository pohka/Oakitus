#ifndef BASE_EVENT_H
#define BASE_EVENT_H

#include "event_listener.h"
#include <vector>
#include "../core/types.h"

namespace oak
{
  class BaseEvent
  {
    
    uchar id;


  public:
    BaseEvent(uchar eventID);

    uchar getEventID();
    //void addListener(EventListener* listener);
    //void fire();

  //protected:
   // std::vector<EventListener*> listeners;
  };
}

#endif