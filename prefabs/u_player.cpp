#include "u_player.h"
#include <oak.h>
#include "../abilitys/shoot.h"

using namespace game::prefab;
using namespace oak;
using namespace game::ability;

UPlayer::UPlayer()
{
  name = "u_player";
  Sprite* sprite = new Sprite("player.png", 0, 0, 32, 40, 32.0f, 40.0f, NULL);
  addComponent(sprite);
  addAbility(new Shoot());
  //addCollision(new CollisionRect(0.0f, 0.0f, 32.0f, 40.0f));
}

UPlayer::~UPlayer()
{

}