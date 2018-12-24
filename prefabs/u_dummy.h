#ifndef U_DUMMY_H
#define U_DUMMY_H

#include "../unit.h"

namespace game
{
  namespace prefab
  {
    class UDummy : public Unit
    {
      public:
        UDummy();
        ~UDummy();

        void onCreate();
    };
  }
}

#endif