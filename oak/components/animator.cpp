#include "animator.h"
#include <oak_def.h>
#include "../core/entity.h"

using namespace oak;

Animator::Animator(uchar baseAnimType, SpriteAnimation* baseAnimation)
{
  this->baseAnim = baseAnimType;
  anims[baseAnimType] = baseAnimation;
  this->curAnim = baseAnimType;
  this->direction = ANIM_DIRECTION_RIGHT;
  baseAnimation->animator = this;
}

Animator::~Animator()
{
  for (auto itr = anims.begin(); itr != anims.end(); itr++)
  {
    delete (itr->second);
  }
  anims.clear();
}

void Animator::addAnim(const uchar animType, SpriteAnimation* animation)
{
  anims[animType] = animation;
  animation->animator = this;
}

void Animator::onUpdate()
{
  if (curAnim > 0)
  {
    bool hasEnded = anims.at(curAnim)->onUpdate(direction, hasChangedDirection);
    if (hasEnded && curAnim != baseAnim)
    {
      setAnim(baseAnim, true);
    }
  }
  hasChangedDirection = false;
}

void Animator::onDraw() const
{
  if (curAnim > 0)
  {
    anims.at(curAnim)->onDraw(entity->position.x, entity->position.y);
  }
}

void Animator::setAnim(const uchar animType, const bool ignorePriority)
{
  if (curAnim == animType)
  {
    return;
  }

  //if animation type doesn't exist
  if (anims.find(animType) == anims.end())
  {
    //this is a fallback to is to display nothing, which make it obvious there is a visual problem with the animation
    curAnim = 0; 
  }
  //if animation exists
  //only set the animation if the priority is equal or greater than the current animation's prioirty
  //ignorePrioirty can force an animation change regardless of the priority
  else
  {
    SpriteAnimation* curAnimPtr = anims.at(curAnim);
    
    if (ignorePriority || curAnimPtr->getPriority() <= anims.at(animType)->getPriority())
    {
      curAnim = animType;
      curAnimPtr->reset();
    }
  }
}

uchar Animator::getCurAnimType() const
{
  return curAnim;
}


uchar Animator::getDirection() const
{
  return direction;
}

void Animator::setDirection(uchar direction)
{
  if (this->direction != direction)
  {
    hasChangedDirection = true;
    this->direction = direction;
  }
}