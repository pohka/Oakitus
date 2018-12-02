#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <core/component.h>
#include "sprite_animation.h"
#include <unordered_map>
#include <core/types.h>

namespace oak
{
  

  class Animator : public Component
  {

    std::unordered_map<uchar, SpriteAnimation*> anims;
    uchar curAnim = 0;

    public:
      Animator();
      ~Animator();

      void addAnim(uchar animType, SpriteAnimation* animation);
      void setAnim(uchar animType);
      uchar getCurAnimType();

      void onUpdate() override;
      void onDraw() const override;
  };
}

#endif