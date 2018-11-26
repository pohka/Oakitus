#include "u_player.h"
#include <oak.h>

using namespace game;
using namespace oak;

UPlayer::UPlayer()
{
  Sprite* sprite = new Sprite("player.png", 0, 0, 32, 40, 32.0f, 40.0f, NULL);
  addComponent(*sprite);
}

UPlayer::~UPlayer()
{

}