#include "actor.h"

using namespace oak;

Actor::Actor() : Entity(true)
{

}

Actor::~Actor()
{

}

Player* Actor::getOwner()
{
  return owner;
}
