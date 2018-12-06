#ifndef EVENT_H
#define EVENT_H

#include "../core/types.h"
#include <vector>
#include <debug.h>

namespace oak
{
  //event data interface
  struct IEventData {};

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
    std::vector<Listener*> listeners; ///all the listeners for this event
    void(*onFire)(Listener*, Data&); ///callback function pointer

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

    ///notify all listeners
    void fire(IEventData& data) override
    {
      Data& customData = static_cast<Data&>(data);

      for (uint i = 0; i < listeners.size(); i++)
      {
        onFire(listeners[i], customData);
      }
    }

    ///add a listener to this event
    void addListener(Listener* listener)
    {
      listeners.push_back(listener);
    }

    ///remove a listener to this event
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

  static uint listenerIDCount = 0; ///counter for listenerID auto increment

  ///generic listener
  template <typename mEvent, typename Listener>
  class BaseListener
  {
    uint listenerID;
    uchar eventID;

    public:
      ///adds this listener to the event manager when constructed
      BaseListener(uchar eventID)
      {
        listenerID = listenerIDCount;
        listenerIDCount++;
        this->eventID = eventID;
        Listener* li = static_cast<Listener*>(this);
        oak::addEventListener<mEvent, Listener>(eventID, li);
      }

      ///removes this listener to the event manager when deconstructed
      ~BaseListener()
      {
        oak::removeEventListener<mEvent>(eventID, listenerID);
      }

      ///returns the listenerID
      uint getListenerID()
      {
        return listenerID;
      }
  };
}

#endif