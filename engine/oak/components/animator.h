#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <oak/core/component.h>
#include "sprite_animation.h"
#include <unordered_map>
#include <oak/core/types.h>
#include <glm/glm.hpp>

namespace oak
{


  ///<summary>Controlling the animations, a set animation will only play if it has a greater or equal prioirty to the current animation</summary>
  class Animator : public Component
  {
    friend struct Fallback;
    friend class SpriteAnimation;

    std::unordered_map<uchar, SpriteAnimation*> anims; ///<summary>Map of the animatons available</summary>
    uchar curAnimID; ///<summary>Current animation key</summary>
    uchar initialAnimID; ///<summary>Base animation key</summary>
    uchar direction; ///<summary>Direction of the current animation</summary>
    bool hasChangedDirection = false; ///<summary>True if the direction of the animation has changed this frame</summary>
    static cnum ANIM_INVALID = 255;
    uint frameIndex = 0; //current frame index

    public:
      Animator(uchar initialAnimID, SpriteAnimation* initialAnimation);
      ~Animator();

      ///<summary>Add an animation with a key</summary>
      void addAnim(uchar animID, SpriteAnimation* animation);

      ///<summary>Sets the current animation, if ignorePrioirty is true it will ignore the prioity checks</summary>
      void setAnim(uchar animID, const bool ignorePriority = false);

      ///<summary>Returns the current animation id</summary>
      uchar getCurAnimID() const;

      ///<summary>Returns the current direction of the animation</summary>
      uchar getDirection() const;

      ///<summary>sets the current direction</summary>
      void setDirection(uchar direction);


    protected:
      ///<summary>Updates the current animation</summary>
      void onTick() override;

      ///<summary>calls onDraw() for the the current animation</summary>
      void onRender() const override;

  };
}

#endif