#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "types.h"
#include "id_generator.h"

#include <map>
#include <glm/glm.hpp>
#include <string>
#include <queue>
#include "../components/collision_layer.h"

namespace oak
{
  class Script;
  class Component;
  class IDGenerator;
  class BaseCollisionShape;

  class Entity
  {
    friend class Oakitus;
    friend class Collision;

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
    std::vector<BaseCollisionShape*> collisionShapes;
	  IDGenerator componentIDGen;
    CollisionLayer collisionLayer;


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
      void addCollision(BaseCollisionShape* shape);
      void instantiate();
      void instantiate(float x, float y);
	    void destroy();
	    uint getID() const;
      CollisionLayer getCollisionLayer() const;
      std::string getName() const;
      virtual void onStart();
	    virtual void onDestroy();
	    virtual void onDraw() const;
	    virtual void onUpdate();
      virtual void onDebugDraw() const;
      virtual void notifyCollision() const;
  };
}

#endif