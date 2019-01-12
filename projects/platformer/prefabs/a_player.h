#ifndef A_PLAYER_H
#define A_PLAYER_H

#include <oak/oak.h>
#include "unit.h"

namespace plat
{
  struct APlayer : public Unit
  {
    APlayer();

    void onGroundTouch() override;
  };
}

#endif