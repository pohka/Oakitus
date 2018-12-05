#include "event_manager.h"
#include <debug.h>
#include "base_event.h"

using namespace oak;

std::vector<BaseEvent*> EventManager::eventList;

void EventManager::addEvent(BaseEvent* event)
{
  eventList.push_back(event);
}

BaseEvent* EventManager::getEventByID(uchar id)
{
  for (uint i = 0; i < eventList.size(); i++)
  {
    if (eventList[i]->getEventID() == id)
    {
      return eventList[i];
    }
  }
  LOG_WARNING << "Event not found with id:" << id;
  return nullptr;
}

void EventManager::addListener(uchar eventID, EventListener* listener)
{
  BaseEvent* baseEvent = getEventByID(eventID);
  baseEvent->addListener(listener);
}