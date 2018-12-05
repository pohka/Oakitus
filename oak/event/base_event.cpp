#include "base_event.h"

using namespace oak;

BaseEvent::BaseEvent(uchar eventID)
{
  id = eventID;
}

uchar BaseEvent::getEventID()
{
  return id;
}

//void BaseEvent::addListener(EventListener* listener)
//{
//  listeners.push_back(listener);
//}

//void BaseEvent::fire()
//{
//  for (uint i = 0; i < listeners.size(); i++)
//  {
//    listeners[i]->onFire();
//  }
//}