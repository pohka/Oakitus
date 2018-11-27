#include "u_player.h"
#include <oak.h>
#include "../abilitys/shoot.h"

using namespace game;
using namespace oak;
using namespace ability;

UPlayer::UPlayer()
{
  Sprite* sprite = new Sprite("player.png", 0, 0, 32, 40, 32.0f, 40.0f, NULL);
  addComponent(*sprite);
  addAbility(*new Shoot());
}

UPlayer::~UPlayer()
{

}