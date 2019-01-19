#include "actor.h"

using namespace oak;

Actor::Actor(const uchar ENTITY_GROUP) : Entity(true, ENTITY_GROUP)
{

}

Player* Actor::getOwner()
{
  return owner;
}
