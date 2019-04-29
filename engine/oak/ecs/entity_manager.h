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

//Returns an Entity with a matching ID if it exists in the world
    static Entity* findEntityByID(uint id);
    //Returns an Entity with a matching name if it exists in the world
    static Entity* findEntityByName(std::string name);
    //
    static std::vector<Entity*> getGlobalEntitys();
    //Destroys the Entity with a matching ID if it exists
    static void destroyEntityByID(uint id);

    //Calls onUpdate() for all Entitys in the world
    static void tickInstances(const uchar TICK_GROUP);

    //Calls onDraw() for all the Entitys in the world
    static void drawInstances();

    //Call onDebugDraw() for all the Entitys in the world
    static void debugDrawInstances();

    //Destroys all the Entitys that are queued to be destroyed
    static void destroyQueuedInstances();

    //Deletes all the Entitys in the world
    static void deleteAllEnts(bool isGlobalExempt = true);

    //Adds all the queued Entitys to the world
    static void instantiateQueuedEnts();

    //Clears and deallocates all the existing queues
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