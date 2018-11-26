#include "unit.h"

using namespace game;


Unit::Unit()
{
  Player* owner = nullptr;
}

Unit::~Unit()
{

}

Player* Unit::getOwner()
{
  return owner;
}

void Unit::setOwner(Player& player)
{
  owner = &player;
}

bool Unit::hasOwner()
{
  return (owner != nullptr);
}