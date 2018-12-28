#ifndef COMPONENT_H
#define COMPONENT_H

#include "types.h"
#include <oak/oak_def.h>

namespace oak
{
  class Entity;

  ///<summary>Defines a behaviour or functionalty to an Entity</summary>
  class Component
  {
	  friend class Entity;
	  uint componentID; ///<summary>An ID that is unique for the owner Entity</summary>

    public:
	    Component(uchar tickGroup = TICK_GROUP_DEFAULT);
	    virtual ~Component();

      uchar getTickGroup() const;
      uint getComponentID() const;
     
    protected:
	    oak::Entity* entity; ///<summary>The owner Entity</summary>

       //EVENTS
      //---------------------------------------
      ///<summary>Called once when the Entity is added to the world</summary>
      virtual void onCreate();

      

      ///<summary>Do logic, called once each frame</summary>
      virtual void onTick();


      ///<summary>Draw, called once each frame</summary>
      virtual void onDraw() const;

      ///<summary>Draw for debuging, called once each frame</summary>
      virtual void onDebugDraw() const;

      ///<summary>Called when the owner has entered a collision</summary>
      virtual void onCollisionHit(Entity& hit);
      //---------------------------------------

    private:
      uchar tickGroup = TICK_GROUP_DEFAULT;
  };
}

#endif