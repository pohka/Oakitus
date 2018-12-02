#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <core/component.h>
#include "sprite_animation.h"
#include <unordered_map>
#include <core/types.h>

namespace oak
{
  cnum ANIM_DIRECTION_RIGHT = 0;
  cnum ANIM_DIRECTION_LEFT = 1;

  class Animator : public Component
  {

    std::unordered_map<uchar, SpriteAnimation*> anims;
    uchar curAnim;
    uchar baseAnim;
    uchar direction;
    bool hasChangedDirection = false;

    public:
      Animator(uchar baseAnimType, SpriteAnimation* baseAnimation);
      ~Animator();

      void addAnim(uchar animType, SpriteAnimation* animation);
      void setAnim(uchar animType, const bool ignorePriority = false);
      uchar getCurAnimType() const;
      uchar getDirection() const;
      void setDirection(uchar direction);


      void onUpdate() override;
      void onDraw() const override;

  };
}

#endif