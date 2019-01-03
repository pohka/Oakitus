#include "actor.h"

using namespace oak;

Actor::Actor() : Entity(true)
{

}

Actor::~Actor()
{
  Entity::~Entity();
}

Player* Actor::getOwner()
{
  return owner;
}
