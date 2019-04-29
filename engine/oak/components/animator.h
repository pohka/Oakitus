#pragma once
#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <oak/ecs/component.h>
#include "sprite_animation.h"
#include <unordered_map>
#include <oak/core/types.h>
#include <glm/glm.hpp>

namespace oak
{


  //Controlling the animations, a set animation will only play if it has a greater or equal prioirty to the current animation
  class Animator : public Component
  {
    friend struct Fallback;
    friend class SpriteAnimation;

    std::unordered_map<uchar, SpriteAnimation*> anims; //Map of the animatons available
    uchar curAnimID = ANIM_NULL; //Current animation key
    AnimDirection direction; //Direction of the current animation
    bool hasChangedDirection = false; //True if the direction of the animation has changed this frame
    uint frameIndex = 0; //current frame index

    public:

      Animator();
      ~Animator();

      //Add an animation with a key
      void addAnim(uchar animID, SpriteAnimation* animation);

      //Sets the current animation, if ignorePrioirty is true it will ignore the prioity checks
      void setAnim(uchar animID, bool ignorePriority = false);

      //Returns the current animation id
      uchar getCurAnimID() const;

      //Returns the current direction of the animation
      AnimDirection getDirection() const;

      //sets the current direction
      void setDirection(AnimDirection direction);


    protected:
      //Updates the current animation
      void onTick() override;

      //calls onDraw() for the the current animation
      void onRender() const override;

  };
}

#endif