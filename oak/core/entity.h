#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "types.h"
#include "id_generator.h"

#include <map>
#include <glm/glm.hpp>
#include <string>
#include <queue>
#include "../collision/collision_layer.h"

namespace oak
{
  class Script;
  class Component;
  class IDGenerator;
  class BaseCollisionShape;


  ///<summary>An Object in the world</summary>
  class Entity
  {
    friend class Oakitus;
    friend class Collision;

    //STATIC
    //-------------------------------------------------------------

    static std::queue<uint> queuedDestroyEntityIDs; ///<summary>Queued Entitys to be removed from the world</summary>
    static std::queue<Entity*> pendingEntityInstances; ///<summary>Queued Entitys to be added to the world</summary>
    static std::vector<Entity*> entitys; ///<summary>All existing Entitys in the world</summary>
    static IDGenerator entityIDGen; ///<summary>Entity ID generator</summary>

    ///<summary>Calls onUpdate() for all Entitys in the world</summary>
    static void updateInstances(); 

    ///<summary>Calls onDraw() for all the Entitys in the world</summary>
    static void drawInstances(); 

    ///<summary>Call onDebugDraw() for all the Entitys in the world</summary>
    static void debugDrawInstances(); 

    ///<summary>Destroys all the Entitys that are queued to be destroyed</summary>
    static void destroyQueuedInstances(); 

    ///<summary>Deletes all the Entitys in the world</summary>
    static void deleteAllEnts(bool isGlobalExempt = true); 

    ///<summary>Adds all the queued Entitys to the world</summary>
    static void instantiateQueuedEnts(); 

    ///<summary>Clears and deallocates all the existing queues</summary>
    static void clearQueues(); 

    //-------------------------------------------------------------


	  uint entityID; ///<summary>Unique ID of this Entity</summary>
	  std::vector<Component*> components; ///<summary>All of the Components added to this Entity</summary>
    std::vector<BaseCollisionShape*> collisionShapes; ///<summary>All of the CollisionShapes added to this Entity</summary>
	  IDGenerator componentIDGen; ///<summary>ID generator for components that are added to this Entity</summary>
    

    public:
      friend class Scene;

      //STATIC
      //-------------------------------------------------------------
      ///<summary>Returns an Entity with a matching ID if it exists in the world</summary>
      static Entity* findEntityByID(uint id);
      ///<summary>Returns an Entity with a matching name if it exists in the world</summary>
      static Entity* findEntityByName(std::string name);
      ///<summary></summary>
      static std::vector<Entity*> getGlobalEntitys(); 
      ///<summary>Destroys the Entity with a matching ID if it exists</summary>
      static void destroyEntityByID(uint id);
      //-------------------------------------------------------------
      

      glm::vec3 position; ///<summary>World position of this Entity</summary>
      int layerID; ///<summary>Drawing layerID</summary>
      bool isGlobal; ///<summary>If true this Entity won't be destroyed at the end of a Scene</summary>
      std::string name; ///<summary>Name of this Entity</summary>
      bool m_isFallback;

	    Entity(bool isFallback = false);
	    virtual ~Entity();
      
      ///<summary>Adds a Component to this Entity</summary>
	    void addComponent(Component* component);

      ///<summary>Adds a CollisionShape to this Entity</summary>
      void addCollision(BaseCollisionShape* shape); 

      ///<summary>Adds this Entity to the world</summary>
      void instantiate();

      ///<summary>Adds this Entity to the world at the given position</summary>
      void instantiate(float x, float y);

      ///<summary>Destroys this Entity</summary>
	    void destroy();

      ///<summary>Returns the Entity ID</summary>
	    uint getID() const;

      ///<summary>Returns the CollisionLayer of this Entity</summary>
      CollisionLayer getCollisionLayer() const;

      ///<summary>Returns the name of this Entity</summary>
      std::string getName() const;

    protected:
      ///<summary>Catagory of this Entity in the collision system</summary> 
      CollisionLayer collisionLayer;

      //EVENTS
      //-------------------------------------------------------------
      ///<summary>Called once when this Entity is added to the world</summary>
      virtual void onStart();

      ///<summary>Called once each frame</summary>
      virtual void onUpdate();

      ///<summary>Draws all renderable components each frame</summary>
      virtual void onDraw() const;

      virtual void onDebugDraw() const;

      ///<summary>Called once just before this Entity is removed from the world and deallocated</summary>
	    virtual void onDestroy();

      ///<summary>Called when a collision occured</summary>
      virtual void notifyCollision(Entity& hit) const;
      //-------------------------------------------------------------

      
  };
}

#endif