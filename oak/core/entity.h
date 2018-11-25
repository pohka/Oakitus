#ifndef ENTITY_H
#define ENTITY_H

#include "script.h"
#include "component.h"

#include <vector>
#include "id_generator.h"
#include "types.h"

#include <map>
#include <glm/glm.hpp>
#include <string>
#include <queue>

namespace oak
{
  class Entity
  {
    friend class Oakitus;
    static std::queue<uint> destroyEntIDQueue;
    static std::vector<Entity*> entitys;
    static IDGenerator entityIDGen;

	  uint entityID;
	  std::vector<Component*> components;
	  std::vector<Script*> scripts;
	  IDGenerator componentIDGen;


    public:
      static void addEntity(Entity& entity);
      static void deleteAllEntitys();
      //static void deleteAllNonGlobalEntitys();
      static void destroyEntityByID(uint entityID);
      static Entity* findEntityByID(uint id);
      static Entity* findEntityByName(std::string name);
      static std::vector<Entity*> getGlobalEntitys();

      glm::vec3 position;
      int layerID;
      bool isGlobal;
      std::string name;

	    Entity();
	    ~Entity();
	    void addComponent(Component& component);
	    void addScript(Script& script);
	    void destroy();
	    uint getID();
      std::string getName();
	    virtual void onDestroy();
	    virtual void onDraw();
	    virtual void onUpdate();
  };
}

#endif