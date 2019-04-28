#pragma once
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <queue>
#include <vector>
#include <oak/ecs/entity.h>
#include "id_generator.h"

namespace oak
{
  //future request to destroy an entity
  struct DestroyRequest
  {
    uint entID;
    float destroyTime; //in game time
  };

  struct EntityManager
  {

///<summary>Returns an Entity with a matching ID if it exists in the world</summary>
    static Entity* findEntityByID(uint id);
    ///<summary>Returns an Entity with a matching name if it exists in the world</summary>
    static Entity* findEntityByName(std::string name);
    ///<summary></summary>
    static std::vector<Entity*> getGlobalEntitys();
    ///<summary>Destroys the Entity with a matching ID if it exists</summary>
    static void destroyEntityByID(uint id);

    ///<summary>Calls onUpdate() for all Entitys in the world</summary>
    static void tickInstances(const uchar TICK_GROUP);

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

    static std::vector<Entity*>& getAllEntitys();

    static void getAllEntitysByGroup(const uchar ENTITY_GROUP, std::vector<Entity*>& out);

    static void queueEntityCreate(Entity* ent);
    static void queueEntityDestroy(Entity* ent);

    static const uint nextEntityID();

    static void requestDestroy(const uint entID, const float delay);
    static void checkRequestedDestroys();



  private:
    static IDGenerator entityIDGen;
    static std::queue<uint> queuedDestroyEntityIDs; //Queued Entitys to be removed from the world this frame
    static std::queue<Entity*> pendingEntityInstances; //Queued Entitys to be added to the world
    static std::vector<Entity*> entitys; //All existing Entitys in the world
    static std::vector<DestroyRequest> destroyRequests; //entities to be removed in the future
  };
}

#endif