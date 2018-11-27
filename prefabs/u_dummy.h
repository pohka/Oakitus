#ifndef U_DUMMY_H
#define U_DUMMY_H

#include <core/entity.h>

namespace game
{
  namespace prefab
  {
    class UDummy : public oak::Entity
    {
    public:
      UDummy();
      ~UDummy();

    };
  }
}

#endif