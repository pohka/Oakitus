#ifndef ALT_EVENT_H
#define ALT_EVENT_H

#include <vector>

namespace oak
{
  //event data interface
  struct AltEventData
  {

  };

  //interface
  struct AltBaseEvent
  {
    AltBaseEvent(const unsigned short id) : eventID(id) {}
    const unsigned short eventID;
  };

  //an event
  template<typename Data>
  struct AltEvent : public AltBaseEvent
  {
    AltEvent(const unsigned short id) : AltBaseEvent(id) {}
    void(*execute)(const Data&);
  };

  //event manager
  struct AltEventManager
  {
    //rigger the event
    template<typename Data>
    static void triggerEvent(unsigned short eventID, const AltEventData& data)
    {
      for (AltBaseEvent* evt : events)
      {
        if (evt->eventID == eventID)
        {
          AltEvent<Data>* castedEvent = static_cast<AltEvent<Data>*>(evt);
          const Data& castedData = static_cast<const Data&>(data);
          castedEvent->execute(castedData);
        }
      }
    }

    //add an event
    template<typename Data>
    static void addEvent(const unsigned short eventID, void(*func)(const Data&))
    {
      AltEvent<Data>* evt = new AltEvent<Data>(eventID);
      evt->execute = func;
      events.push_back(evt);
    }

  private:
    static std::vector<AltBaseEvent*> events;
  };
}

#endif