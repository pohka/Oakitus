#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <oak/core/types.h>
#include <oak/oak_def.h>
#include <oak/time/interval_ticker.h>

namespace oak
{
  class Entity;

  //Defines a behaviour or functionalty to an Entity
  class Component
  {
	  friend class Entity;

    static uint reflectAutoIncID;

	  uint componentID; //An ID that is unique for the owner Entity

    

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
      //Called once when the Entity is added to the world
      virtual void onCreate();

      //Do logic, called once each frame
      virtual void onTick();

      //Draw, called once each frame
      virtual void onRender() const;

      //Draw for debuging, called once each frame
      virtual void onDebugDraw() const;

      virtual void onDestroy();

      //Called when the owner has entered a collision
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