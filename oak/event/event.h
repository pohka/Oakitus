#ifndef EVENT_H
#define EVENT_H

#include "../core/types.h"
#include <vector>
#include <debug.h>

namespace oak
{
  //event data interface
  struct IEventData
  {
  };

  //event base class
  class IEvent
  {
    uchar id;

    public:
      IEvent(uchar id)
      {
        this->id = id;
      }

      uchar getID()
      {
        return id;
      }

      virtual void fire(oak::IEventData& data) = 0;
  };

  //generic event
  template <typename Listener, typename Data>
  class Event : public IEvent
  {
    std::vector<Listener*> listeners;
    void(*onFire)(Listener*, Data&);

  public:
    Event(uchar eventID, void(*onFire)(Listener*, Data&)) : IEvent(eventID)
    {
      this->onFire = onFire;
    }

    ~Event()
    {
      for (Listener* listener : listeners)
      {
        delete listener;
      }
      listeners.clear();
    }

    void fire(IEventData& data) override
    {
      Data& customData = static_cast<Data&>(data);

      for (uint i = 0; i < listeners.size(); i++)
      {
        onFire(listeners[i], customData);
      }
    }

    void addListener(Listener* listener)
    {
      listeners.push_back(listener);
    }

    void removeListener(uint listenerID)
    {
      for (uint i = 0; i < listeners.size(); i++)
      {
        if (listeners[i]->getListenerID() == listenerID)
        {
          listeners.erase(listeners.begin() + i);
          LOG << "removed listener";
          return;
        }
      }
      LOG_WARNING << "Listener was not found with listenerID:" << listenerID << 
        ", eventID:" << getID();
    }
  };

  static uint listenerIDCount = 0;

  //listener interface
  template <typename mEvent, typename Listener>
  class BaseListener
  {
    uint listenerID;
    uchar eventID;

    public:

      BaseListener(uchar eventID)
      {
        listenerID = listenerIDCount;
        listenerIDCount++;
        this->eventID = eventID;
        Listener* li = static_cast<Listener*>(this);
        oak::addEventListener<mEvent, Listener>(eventID, li);
      }

      ~BaseListener()
      {
        oak::removeEventListener<mEvent>(eventID, listenerID);
      }

      uint getListenerID()
      {
        return listenerID;
      }
  };
}

#endif