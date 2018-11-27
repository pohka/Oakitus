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
  class Script;

  class Entity
  {
    friend class Oakitus;
    static std::queue<uint> queuedDestroyEntityIDs;
    static std::queue<Entity*> pendingEntityInstances;
    static std::vector<Entity*> entitys;
    static IDGenerator entityIDGen;

    static void updateInstances();
    static void drawInstances();
    static void destroyQueuedInstances();
    static void deleteAllEnts(bool isGlobalExempt);
    static void instantiateQueuedEnts();
    static void clearQueues();

	  uint entityID;
	  std::vector<Component*> components;
	  std::vector<Script*> scripts;
	  IDGenerator componentIDGen;


    public:
      friend class Scene;
      static Entity* findEntityByID(uint id);
      static Entity* findEntityByName(std::string name);
      static std::vector<Entity*> getGlobalEntitys();
      static void destroyEntityByID(uint id);
      

      glm::vec3 position;
      int layerID;
      bool isGlobal;
      std::string name;

	    Entity();
	    virtual ~Entity();
	    void addComponent(Component& component);
	    void addScript(Script& script);
      void instantiate();
      void instantiate(float x, float y);
	    void destroy();
	    uint getID();
      std::string getName();
      virtual void onStart();
	    virtual void onDestroy();
	    virtual void onDraw();
	    virtual void onUpdate();
  };
}

#endif