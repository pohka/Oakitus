#ifndef ARROW_H
#define ARROW_H

#include <core/entity.h>

namespace game
{
  class Arrow : public oak::Entity
  {

    public:
      Arrow(float x, float y);
      ~Arrow();
  };
}

#endif