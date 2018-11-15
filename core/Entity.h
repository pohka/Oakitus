#ifndef ENTITY_H
#define ENTITY_H

#include "Script.h"
#include "Component.h"

#include <vector>
#include "Vector3.h"
#include "IDGenerator.h"
#include "Types.h"

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