#ifndef COMPONENT_H
#define COMPONENT_H

#include "Types.h"

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
	    static uint getNextID();
	    virtual void onUpdate();
	    virtual void onDraw();

    protected:
	    oak::Entity* entity;

  };
}

#endif