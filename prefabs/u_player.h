#ifndef U_PLAYER_H
#define U_PLAYER_H

#include "../unit.h"

namespace game
{
  namespace prefab
  {
    class UPlayer : public Unit
    {
      public:
        UPlayer();
        ~UPlayer();

        void onCreate();
    };
  }
}

#endif