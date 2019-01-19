#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <oak/core/types.h>
#include "id_generator.h"

#include <map>
#include <glm/glm.hpp>
#include <string>
#include <queue>
#include <oak/collision/collision_layer.h>
#include <oak/components/base_rigid_body.h>
#include <oak/components/transform.h>

#include <unordered_map>

namespace oak
{
  class Script;
  class Component;
  struct IDGenerator;
  class BaseCollisionShape;


  ///<summary>An Object in the world</summary>
  class Entity
  {
    friend struct EntityManager;

	  uint entityID; ///<summary>Unique ID of this Entity</summary>

    std::vector<Component*> componentGroups[TICK_GROUP_MAX];
    
	  IDGenerator componentIDGen; ///<summary>ID generator for components that are added to this Entity</summary>
    
    

    public:
      friend class Scene;

      Transform* transform;
      int layerID; ///<summary>Drawing layerID</summary>
      bool isGlobal; ///<summary>If true this Entity won't be destroyed at the end of a Scene</summary>
      std::string name; ///<summary>Name of this Entity</summary>
      const uchar ENTITY_GROUP;
      

	    Entity(bool isEverRendered = true, const uchar ENTITY_GROUP = ENTITY_GROUP_NONE);
	    virtual ~Entity();
      
      ///<summary>Adds a Component to this Entity</summary>
	    void addComponent(Component* component);

      ///<summary>Adds a CollisionShape to this Entity</summary>
      void addCollision(BaseCollisionShape* shape); 

      void addRigidBody(BaseRigidBody* rigidBody);

      ///<summary>Adds this Entity to the world at zero zero</summary>
      void create();

      ///<summary>Adds this Entity to the world at the given position</summary>
      void create(float x, float y);

     // void createAsChild(Entity* child);

      ///<summary>Destroys this Entity</summary>
	    void destroy();

      ///<summary>Returns the Entity ID</summary>
	    uint getID() const;

      ///<summary>Returns the CollisionLayer of this Entity</summary>
      const uint getCollisionLayer() const;

      ///<summary>Returns the name of this Entity</summary>
      std::string getName() const;

      bool getIsTickingEnabled() const;
      void setIsTickingEnabled(bool isEnabled);

      void setIsRenderable(bool isRenderable);
      bool getIsRenderable() const;

      bool getCanTickWhenPaused() const;

      bool canTickThisFrame() const;

      //find a component by class using dynamic casting
      template <typename T>
      T* getComponent()
      {
        T* casted;
        for (uchar i = 0; i < TICK_GROUP_MAX; i++)
        {
          for (Component* comp : componentGroups[i])
          {
            casted = dynamic_cast<T*>(comp);
            if (casted != nullptr)
            {
              return casted;
            }
          }
        }
        return nullptr;
      }

      //find all components by class using dynamic casting
      template <typename T>
      void getComponents(std::vector<T*>& out)
      {
        T* casted;
        for (uchar i = 0; i < TICK_GROUP_MAX; i++)
        {
          for (Component* comp : componentGroups[i])
          {
            casted = dynamic_cast<T*>(comp);
            if (casted != nullptr)
            {
              out.push_back(casted);
            }
          }
        }
      }

      //find a component by reflection id
      template <typename T>
      T* getComponentWithReflection(const uint REFLECT_ID)
      {
        for (uchar i = 0; i < TICK_GROUP_MAX; i++)
        {
          for (Component* comp : componentGroups[i])
          {
            if (comp->_REFLECT_ID == REFLECT_ID)
            {
              return reinterpret_cast<T*>(comp);
            }
          }
        }
        return nullptr;
      }

      //find all components by reflection id
      template <typename T>
      void getComponentsWithReflection(const uint REFLECT_ID, std::vector<T*>& out)
      {
        for (uchar i = 0; i < TICK_GROUP_MAX; i++)
        {
          for (Component* comp : componentGroups[i])
          {
            if (comp->_REFLECT_ID == REFLECT_ID)
            {
              out.push_back(reinterpret_cast<T*>(comp));
            }
          }
        }
      }

      //attachs a child to this entity, the child is created if it is not already created
      void addChild(Entity* child);

      //detached this entity from it's parent
      void detach();

      //find child with matching name, returns nullptr if not found
      Entity* findChildByName(std::string name);

      //find child with matching id, returns nullptr if not found
      Entity* findChildByID(uint id);

      //returns the parent entity, returns nullptr if no parent is set
      const Entity* getParent() const;

      //get all the child entities
      const std::vector<Entity*>& getChildren() const;

      //get the collision shapes
      std::vector<BaseCollisionShape*>& getCollisionShapes();

      ///<summary>Called when a collision occured</summary>
      void onCollisionHit(Entity& hit);

      BaseRigidBody* getRigidBody() const;

      void setCreationState(const uchar state);
      const uchar getCreationState() const;

    protected:
      ///<summary>Catagory of this Entity in the collision system</summary> 
      uint collisionLayer = COLLISION_LAYER_DEFAULT;
      BaseRigidBody* rigidBody = nullptr;

      //EVENTS
      //-------------------------------------------------------------
      ///<summary>Called once when this Entity is added to the world</summary>
      void onCreate();

      ///<summary>Called once each frame</summary>
      void onTick(const uchar TICK_GROUP);

      ///<summary>Draws all renderable components each frame</summary>
      void onRender() const;

      void onDebugDraw() const;

      ///<summary>Called once just before this Entity is removed from the world and deallocated</summary>
	    void onDestroy();

      

      

      //-------------------------------------------------------------

      std::vector<BaseCollisionShape*> collisionShapes; ///<summary>All of the CollisionShapes added to this Entity</summary>

      bool canTickWhenPaused = false;

      std::vector<Entity*> children; //child entities
      Entity* parent = nullptr; //parent entity

    private:
       bool isEverRendered;
       bool isRenderable;
       bool isTickingEnable = true;

       
       uchar creationState = CREATION_STATE_NULL; //current creation state
  };
}

#endif