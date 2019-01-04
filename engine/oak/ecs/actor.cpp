#include "actor.h"

using namespace oak;

Actor::Actor() : Entity(true)
{

}

Player* Actor::getOwner()
{
  return owner;
}
