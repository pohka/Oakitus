#include "player.h"

using namespace oak;
using namespace game;

IDGenerator Player::idGen = IDGenerator();


Player::Player()
{
  playerID = idGen.nextID();
}

Player::~Player()
{

}

uint Player::getID()
{
  return playerID;
}
