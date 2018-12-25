#include "event_manager.h"
#include <oak/debug.h>

using namespace oak;

std::vector<IEvent*> EventManager::events;

void EventManager::addEvent(IEvent* event)
{
  events.push_back(event);
}

IEvent* EventManager::getEvent(uchar id)
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