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
    uchar curAnim;
    uchar baseAnim;
    

    public:
      Animator(uchar baseAnimType, SpriteAnimation* baseAnimation);
      ~Animator();

      void addAnim(uchar animType, SpriteAnimation* animation);
      void setAnim(uchar animType, const bool ignorePriority = false);
      uchar getCurAnimType() const;


      void onUpdate() override;
      void onDraw() const override;

  };
}

#endif