#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "types.h"
#include "id_generator.h"

#include <map>
#include <glm/glm.hpp>
#include <string>
#include <queue>

namespace oak
{
  class Script;
  class Component;
  class IDGenerator;
  class CollisionShape;

  class Entity
  {
    friend class Oakitus;
    static std::queue<uint> queuedDestroyEntityIDs;
    static std::queue<Entity*> pendingEntityInstances;
    static std::vector<Entity*> entitys;
    static IDGenerator entityIDGen;

    static void updateInstances();
    static void drawInstances();
    static void debugDrawInstances();
    static void destroyQueuedInstances();
    static void deleteAllEnts(bool isGlobalExempt);
    static void instantiateQueuedEnts();
    static void clearQueues();

	  uint entityID;
	  std::vector<Component*> components;
	  std::vector<Script*> scripts;
    std::vector<CollisionShape*> collisionShapes;
	  IDGenerator componentIDGen;
    IDGenerator scriptIDGen;


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
	    void addComponent(Component* component);
      void addCollision(CollisionShape* shape);
	    void addScript(Script* script);
      void instantiate();
      void instantiate(float x, float y);
	    void destroy();
	    uint getID() const;
      std::string getName() const;
      virtual void onStart();
	    virtual void onDestroy();
	    virtual void onDraw() const;
	    virtual void onUpdate();
      virtual void onDebugDraw() const;
  };
}

#endif