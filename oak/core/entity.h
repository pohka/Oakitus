#ifndef ENTITY_H
#define ENTITY_H

#include "script.h"
#include "component.h"

#include <vector>
#include "vector3.h"
#include "id_generator.h"
#include "types.h"

#include <map>

namespace oak
{
  class Entity
  {
	  uint entityID;
	  std::vector<Component*> components;
	  std::vector<Script*> scripts;
	  IDGenerator* idGen;


    public:
	    Vector3* position;
      int layerID;

	    Entity();
	    ~Entity();
	    void addComponent(Component& component);
	    void addScript(Script& script);
	    void destroy();
	    uint getID();
	    virtual void onDestroy();
	    virtual void onDraw();
	    virtual void onUpdate();
  };
}

#endif