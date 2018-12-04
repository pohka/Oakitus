#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <core/component.h>
#include "sprite_animation.h"
#include <unordered_map>
#include <core/types.h>

namespace oak
{


  ///<summary>Controlling the animations, a set animation will only play if it has a greater or equal prioirty to the current animation</summary>
  class Animator : public Component
  {
    friend struct Fallback;

    std::unordered_map<uchar, SpriteAnimation*> anims; ///<summary>Map of the animatons available</summary>
    bool m_isFallback;
    uchar curAnim; ///<summary>Current animation key</summary>
    uchar baseAnim; ///<summary>Base animation key</summary>
    uchar direction; ///<summary>Direction of the current animation</summary>
    bool hasChangedDirection = false; ///<summary>True if the direction of the animation has changed this frame</summary>

    public:
      Animator(uchar baseAnimType, SpriteAnimation* baseAnimation, bool isFallback = false);
      ~Animator();

      ///<summary>Add an animation with a key</summary>
      void addAnim(uchar animType, SpriteAnimation* animation);

      ///<summary>Sets the current animation, if ignorePrioirty is true it will ignore the prioity checks</summary>
      void setAnim(uchar animType, const bool ignorePriority = false);

      ///<summary>Returns the current animation type</summary>
      uchar getCurAnimType() const;

      ///<summary>Returns the current direction of the animation</summary>
      uchar getDirection() const;

      ///<summary>sets the current direction</summary>
      void setDirection(uchar direction);

    protected:
      ///<summary>Updates the current animation</summary>
      void onUpdate() override;

      ///<summary>calls onDraw() for the the current animation</summary>
      void onDraw() const override;

  };
}

#endif