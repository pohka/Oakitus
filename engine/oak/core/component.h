#ifndef COMPONENT_H
#define COMPONENT_H

#include "types.h"
#include <oak/oak_def.h>
#include "interval_ticker.h"

namespace oak
{
  class Entity;

  ///<summary>Defines a behaviour or functionalty to an Entity</summary>
  class Component
  {
	  friend class Entity;

    

	  uint componentID; ///<summary>An ID that is unique for the owner Entity</summary>

    public:
	    Component(cnum tickGroup = TICK_GROUP_DEFAULT, cnum tickingType = TICK_TYPE_TICKABLE, const bool isEverRender = false);
	    virtual ~Component();

      uchar getTickGroup() const;
      uint getComponentID() const;
      bool getIsRenderable() const;

      bool isTickable();
      bool isUsingIntervalTicking();
      float getTickingInterval();
      

      
     
    protected:
	    oak::Entity* entity; ///<summary>The owner Entity</summary>

       //EVENTS
      //---------------------------------------
      ///<summary>Called once when the Entity is added to the world</summary>
      virtual void onCreate();

      ///<summary>Do logic, called once each frame</summary>
      virtual void onTick();

      ///<summary>Draw, called once each frame</summary>
      virtual void onRender() const;

      ///<summary>Draw for debuging, called once each frame</summary>
      virtual void onDebugDraw() const;

      virtual void onDestroy();

      ///<summary>Called when the owner has entered a collision</summary>
      virtual void onCollisionHit(Entity& hit);
      //---------------------------------------

      

      uchar tickingType;
      IntervalTicker ticker;
      
    private:
      uchar tickGroup;
      bool isEverRendered;
      bool isRenderable;

      bool canTickThisFrame();
  };
}

#endif