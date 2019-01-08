#ifndef A_PLAYER_H
#define A_PLAYER_H

#include <oak/oak.h>

namespace plat
{
  struct APlayer : public oak::Actor
  {
    APlayer();

    static cnum STATE_AIR = 1;
    static cnum STATE_GROUND = 2;

    uchar state = STATE_AIR;
  };
}

#endif