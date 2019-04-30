#pragma once
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "event.h"
#include <vector>

namespace oak
{
  //event manager
  struct EventManager
  {
    //trigger the event
    template<typename Data>
    static void triggerEvent(unsigned short eventID, const IEventData& data)
    {
      for (IEvent* evt : events)
      {
        if (evt->eventID == eventID)
        {
          Event<Data>* castedEvent = static_cast<Event<Data>*>(evt);
          const Data& castedData = static_cast<const Data&>(data);
          castedEvent->execute(castedData);
          return;
        }
      }
    }

    //add an event
    template<typename Data>
    static void addEvent(unsigned short eventID, void(*func)(const Data&))
    {
      Event<Data>* evt = new Event<Data>(eventID);
      evt->execute = func;
      events.push_back(evt);
    }

    //remove an event by id
    static void removeEvent(unsigned short eventID)
    {
      for (unsigned int i = 0; i < events.size(); i++)
      {
        if (events[i]->eventID == eventID)
        {
          delete events[i];
          events.erase(events.begin() + i);
          return;
        }
      }
    }

    //remove all events
    static void removeAllEvents()
    {
      for (IEvent* evt : events)
      {
        delete evt;
      }
      events.clear();
    }

  private:
    static std::vector<IEvent*> events;
  };
}

#endif