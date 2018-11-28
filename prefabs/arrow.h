#ifndef ARROW_H
#define ARROW_H

#include <core/entity.h>

namespace game
{
  namespace prefab
  {
    class Arrow : public oak::Entity
    {

      public:
        Arrow(glm::vec2 targetPos);
        ~Arrow();
    };
  }
}

#endif