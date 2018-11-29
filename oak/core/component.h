#ifndef COMPONENT_H
#define COMPONENT_H

#include "types.h"
#include "entity.h"

namespace oak
{
  class Entity;

  class Component
  {
	  friend class Entity;
	  uint componentID;

    public:
	    Component();
	    virtual ~Component();
      virtual void onStart();
	    virtual void onUpdate();
	    virtual void onDraw() const;
      virtual void onDebugDraw() const;

    protected:
	    oak::Entity* entity;

  };
}

#endif