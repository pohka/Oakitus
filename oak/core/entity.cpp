#include "entity.h"
#include "script.h"
#include "component.h"


using namespace oak;

std::vector<Entity*> Entity::entitys;
std::queue<uint> Entity::queuedDestroyEntityIDs;
IDGenerator Entity::entityIDGen = IDGenerator();
std::queue<Entity*> Entity::pendingEntityInstances;


Entity::Entity() 
{
  componentIDGen = IDGenerator();
  scriptIDGen = IDGenerator();
  this->entityID = entityIDGen.nextID();
  this->position = glm::vec3(0, 0, 0);
  layerID = 0;
  isGlobal = false;
  this->name = "ent_" + std::to_string(entityID);
}

Entity::~Entity()
{
  for (Component* c : components)
  {
    delete c;
  }
  for (Script* s : scripts)
  {
    delete s;
  }
}

void Entity::addComponent(Component* component)
{
  component->entity = this;
  component->componentID = componentIDGen.nextID();
  this->components.push_back(component);
}

void Entity::addScript(Script* script)
{
  script->entity = this;
  script->scriptID = scriptIDGen.nextID();
  this->scripts.push_back(script);
}

void Entity::addCollision(CollisionShape* shape)
{
  collisionShapes.push_back(shape);
}

void Entity::instantiate()
{
  Entity::pendingEntityInstances.push(this);
}

void oak::Entity::instantiate(float x, float y)
{
  this->position.x = x;
  this->position.y = y;
  Entity::pendingEntityInstances.push(this);
}

void Entity::destroy()
{
  Entity::queuedDestroyEntityIDs.push(entityID);
}

void Entity::destroyEntityByID(uint id)
{
  Entity::queuedDestroyEntityIDs.push(id);
}

uint Entity::getID() const
{
  return this->entityID;
}

std::string Entity::getName() const
{
  return name;
}

void Entity::onStart()
{
  for (Component* comp : components)
  {
    comp->onStart();
  }
  for (Script* script : scripts)
  {
    script->onStart();
  }
}

void Entity::onDestroy()
{
  
}


void Entity::onDraw() const
{
  for (uint i = 0; i < components.size(); i++) 
  {
    components[i]->onDraw();
  }
}

void Entity::onDebugDraw() const
{
  for(Component* comp : components)
  {
    comp->onDebugDraw();
  }
}

void Entity::onUpdate()
{
  for (uint i = 0; i < components.size(); i++)
  {
    components[i]->onUpdate();
  }

  for (uint i = 0; i < scripts.size(); i++)
  {
    scripts[i]->onUpdate();
  }
}


//static functions
//----------------------------
Entity* Entity::findEntityByID(uint id)
{
  for (uint i = 0; i < entitys.size(); i++)
  {
    if (entitys[i]->getID() == id)
    {
      return entitys[i];
    }
  }

  return nullptr;
}

Entity* Entity::findEntityByName(std::string name)
{
  for (uint i = 0; i < entitys.size(); i++)
  {
    if (entitys[i]->name.compare(name) == 0)
    {
      return entitys[i];
    }
  }

  return nullptr;
}

std::vector<Entity*> Entity::getGlobalEntitys()
{
  std::vector<Entity*> list;
  for (uint i = 0; i < entitys.size(); i++)
  {
    if (entitys[i]->isGlobal)
    {
      list.push_back(entitys[i]);
    }
  }
  return list;
}

void Entity::updateInstances()
{
  for (uint i = 0; i < Entity::entitys.size(); i++)
  {
    Entity::entitys[i]->onUpdate();
  }
}

struct EntityLayerCompare {
  bool operator()(const Entity* l, const Entity* r) {
    return l->layerID < r->layerID;
  }
};


void Entity::drawInstances()
{
  std::sort(Entity::entitys.begin(), Entity::entitys.end(), EntityLayerCompare());

  for (uint i = 0; i < Entity::entitys.size(); i++)
  {
    Entity::entitys[i]->onDraw();
  }
}

void Entity::debugDrawInstances()
{
  for (Entity* ent : entitys)
  {
    ent->onDebugDraw();
  }
}

void Entity::destroyQueuedInstances()
{
  bool found;
  Entity* ent;

  while (!Entity::queuedDestroyEntityIDs.empty())
  {
    uint id = Entity::queuedDestroyEntityIDs.front();
    ent = nullptr;
    found = false;

    //find entity with matching id, then remove from vector
    for (uint i = 0; i < Entity::entitys.size() && !found; i++)
    {
      if (Entity::entitys[i]->getID() == id)
      {
        ent = Entity::entitys[i];
        Entity::entitys.erase(Entity::entitys.begin() + i);
        found = true;
      }
    }
    //call onDestroy and delete the object
    if (found)
    {
      //LOG << "destroyed:" << ent->getName() << ":" << ent->getID();
      ent->onDestroy();
      delete ent;
    }

    Entity::queuedDestroyEntityIDs.pop();
  }
}

void Entity::clearQueues()
{
  while (!queuedDestroyEntityIDs.empty())
  {
    queuedDestroyEntityIDs.pop();
  }

  while (!pendingEntityInstances.empty())
  {
    Entity* ent = pendingEntityInstances.front();
    pendingEntityInstances.pop();
    delete ent;
  }
}

void Entity::deleteAllEnts(bool isGlobalExempt)
{
  if (isGlobalExempt == true)
  {
    for (uint i = 0; i < Entity::entitys.size(); i++)
    {
      Entity* ent = Entity::entitys[i];
      if (ent->isGlobal == false)
      {
        Entity::entitys.erase(Entity::entitys.begin() + i); //remove from vector
        i--;
        delete ent;
      }
    }
  }
  else
  {
    for (uint i = 0; i < Entity::entitys.size(); i++)
    {
      Entity* ent = Entity::entitys[i];
      Entity::entitys.erase(Entity::entitys.begin() + i); 
      i--;
      delete ent;
    }
  }
}

void Entity::instantiateQueuedEnts()
{
  std::queue<Entity*> temp;
  //add all entity instances to the game
  while (!Entity::pendingEntityInstances.empty())
  {
    Entity* ent = Entity::pendingEntityInstances.front();
    Entity::entitys.push_back(ent);
    temp.push(ent);
    Entity::pendingEntityInstances.pop();
  }

  //call onStart() for all the newly instances
  while (!temp.empty())
  {
    temp.front()->onStart();
    temp.pop();
  }
}