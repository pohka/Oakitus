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
      //ticking groups i.e. which stage in the loop should this component tick
      enum class TickGroup : uchar
      {
        DEFAULT = 0,
        DURING_PHYSICS = 1,
        AFTER_PHYSICS = 2,
        LAST = 3
      };
      static const unsigned char TICK_GROUP_COUNT = 4;

      //reflectIDs
      enum class Reflect : uchar
      {
        NONE,
        TRANSFORM,
        ANIMATOR,
        RIGID_BODY_2D,
        SPRITE,
        CHUNK,
        LUA_SCRIPT,
        UNIT
      };

      //ticking behaviour type
      enum class TickType : uchar
      {
        NOT_TICKABLE = 0, //does not tick
        TICKABLE = 1, //ticks every frame
        INTERVAL_TICK = 2 //ticks each interval (if the interval time is zero then it ticks each frame)
      };
      static const uchar TICK_TYPE_COUNT = 3;

	    Component(
        Reflect reflectID = Reflect::NONE,
        TickGroup tickGroup = TickGroup::DEFAULT,
        TickType tickType = TickType::TICKABLE,
        const bool isEverRender = false
      );
	    virtual ~Component();

      TickGroup getTickGroup() const;
      uint getComponentID() const;
      bool getIsRenderable() const;

      bool isTickable() const;
      bool isUsingIntervalTicking() const;
      float getTickingInterval() const;
      const Reflect _REFLECT_ID;
      
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

      

      TickType tickType;
      IntervalTicker ticker;
      
    private:
      TickGroup tickGroup;
      bool isEverRendered;
      bool isRenderable;

      bool canTickThisFrame();
  };
}

#endif