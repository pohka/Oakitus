#ifndef EVENT_LISTENER
#define EVENT_LISTENER

namespace oak
{
  class EventListener
  {
    public:
      virtual void onFire() = 0;
    

  protected:
    //void (*onFire)();
    
  };

  


}

#endif