#pragma once
#ifndef EVENT_H
#define EVENT_H

namespace oak
{
  //event data interface
  struct IEventData {};

  //interface
  struct IEvent
  {
    IEvent(const unsigned short id) : eventID(id) {}
    const unsigned short eventID;
  };

  //an event
  template<typename Data>
  struct Event : public IEvent
  {
    Event(const unsigned short id) : IEvent(id) {}
    void(*execute)(const Data&);
  };
}

#endif