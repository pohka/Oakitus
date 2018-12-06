#ifndef EVENT_H
#define EVENT_H

#include "../core/types.h"
#include <vector>

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
  };
}

#endif