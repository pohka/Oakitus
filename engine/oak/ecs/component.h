#ifndef COMPONENT_H
#define COMPONENT_H

#include <oak/core/types.h>
#include <oak/oak_def.h>
#include <oak/time/interval_ticker.h>

namespace oak
{
  class Entity;

  ///<summary>Defines a behaviour or functionalty to an Entity</summary>
  class Component
  {
	  friend class Entity;

    static uint reflectAutoIncID;

	  uint componentID; ///<summary>An ID that is unique for the owner Entity</summary>

    

    public:
	    Component(const uint REFLECT_ID = REFLECT_NULL, cnum tickGroup = TICK_GROUP_DEFAULT, cnum tickingType = TICK_TYPE_TICKABLE, const bool isEverRender = false);
	    virtual ~Component();

      uchar getTickGroup() const;
      uint getComponentID() const;
      bool getIsRenderable() const;

      bool isTickable() const;
      bool isUsingIntervalTicking() const;
      float getTickingInterval() const;
      const uint _REFLECT_ID;
      
      Entity* getOwnerEntity();
     
    protected:
	    oak::Entity* entity; //The owner Entity

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