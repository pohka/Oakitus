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
      enum class TickGroup : uchar
      {
        DEFAULT = 0,
        DURING_PHYSICS = 1,
        AFTER_PHYSICS = 2,
        LAST = 3
       // COUNT = 4
      };
      static const unsigned char TICK_GROUP_COUNT = 4;

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
      static const uint REFLECT_COUNT = 8;

      //static const uint REFLECT_NULL = 0;
      //static const uint REFLECT_TRANSFORM = 1;
      //static const uint REFLECT_ANIMATOR = 2;
      //static const uint REFLECT_RIGID_BODY_2D = 3;
      //static const uint REFLECT_SPRITE = 4;
      //static const uint REFLECT_CHUNK = 5;
      //static const uint REFLECT_LUA_SCRIPT = 6;
      //static const uint REFLECT_UNIT = 7;
      //static const uint REFLECT_LAST = 7;

	    Component(
        Reflect reflectID = Reflect::NONE,
        TickGroup tickGroup = TickGroup::DEFAULT,
        cnum tickingType = TICK_TYPE_TICKABLE,
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

      

      uchar tickingType;
      IntervalTicker ticker;
      
    private:
      TickGroup tickGroup;
      bool isEverRendered;
      bool isRenderable;

      bool canTickThisFrame();
  };
}

#endif