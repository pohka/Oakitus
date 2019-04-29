#pragma once
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
  class CollisionShape;


  //An Object in the world
  class Entity
  {
    friend struct EntityManager;

    //state of an entity in creation
    enum class CreationState : uchar
    {
      NONE = 0, //not queued or created
      QUEUED = 1, //in queue to be created at the end of the frame
      CREATED = 2, //created and exists in the current scene
      DESTROYED = 3 //queued for destruction
    };

	  uint entityID; //Unique ID of this Entity

    std::vector<Component*> componentGroups[Component::TICK_GROUP_COUNT];
    
	  IDGenerator componentIDGen; //ID generator for components that are added to this Entity
    BaseRigidBody* rigidbody = nullptr;
    
    public:
      friend class Scene;

      Transform* transform;
      int layerID; //Drawing layerID
      bool isGlobal; //If true this Entity won't be destroyed at the end of a Scene
      std::string name; //Name of this Entity
      const uchar ENTITY_GROUP; //grouping for entitys, so they can be found
      

	    Entity(bool isEverRendered = true, const uchar ENTITY_GROUP = ENTITY_GROUP_NONE);
	    virtual ~Entity();
      
      //Adds a Component to this Entity
	    void addComponent(Component* component, const bool isRigidBody = false);
      BaseRigidBody* getRigidBody() const;

      //Adds a CollisionShape to this Entity
      void addCollision(CollisionShape* shape); 

      //Adds this Entity to the world at zero zero
      void create();

      //Adds this Entity to the world at the given position
      void create(float x, float y, float z=0.0f);

      //Destroys this Entity
	    void destroy();

      //Returns the Entity ID
	    uint getID() const;

      //Returns the CollisionLayer of this Entity
      const uint getCollisionLayer() const;

      //Returns the name of this Entity
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
        for (uchar i = 0; i < Component::TICK_GROUP_COUNT; i++)
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
        for (uchar i = 0; i < Component::TICK_GROUP_COUNT; i++)
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
      T* getComponentWithReflection(Component::Reflect reflectID)
      {
        for (uchar i = 0; i < Component::TICK_GROUP_COUNT; i++)
        {
          for (Component* comp : componentGroups[i])
          {
            if (comp->_REFLECT_ID == reflectID)
            {
              return reinterpret_cast<T*>(comp);
            }
          }
        }
        return nullptr;
      }

      //find all components by reflection id
      template <typename T>
      void getComponentsWithReflection(Component::Reflect reflectID, std::vector<T*>& out)
      {
        for (uchar i = 0; i < Component::TICK_GROUP_COUNT; i++)
        {
          for (Component* comp : componentGroups[i])
          {
            if (comp->_REFLECT_ID == reflectID)
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
      Entity* findChildByName(const std::string& name);

      //find child with matching id, returns nullptr if not found
      Entity* findChildByID(uint id);

      //returns the parent entity, returns nullptr if no parent is set
      const Entity* getParent() const;

      //get all the child entities
      const std::vector<Entity*>& getChildren() const;

      //get the collision shapes
      std::vector<CollisionShape*>& getCollisionShapes();

      //Called when a collision occured
      void onCollisionHit(Entity& hit);

      void setCreationState(CreationState state);
      CreationState getCreationState() const;

    protected:
      //Catagory of this Entity in the collision system 
      uint collisionLayer = COLLISION_LAYER_DEFAULT;

      //EVENTS
      //-------------------------------------------------------------
      //Called once when this Entity is added to the world
      void onCreate();

      //Called once each frame
      void onTick(Component::TickGroup tickGroup);

      //Draws all renderable components each frame
      void onRender() const;

      void onDebugDraw() const;

      //Called once just before this Entity is removed from the world and deallocated
	    void onDestroy();
      //-------------------------------------------------------------

      std::vector<CollisionShape*> collisionShapes; //All of the CollisionShapes added to this Entity

      bool canTickWhenPaused = false;

      std::vector<Entity*> children; //child entities
      Entity* parent = nullptr; //parent entity

    private:
       bool isEverRendered;
       bool isRenderable;
       bool isTickingEnable = true;

       
       CreationState creationState = CreationState::NONE; //current creation state
  };
}

#endif