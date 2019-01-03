#include "animator.h"
#include <oak/oak_def.h>
#include <oak/ecs/entity.h>
#include <oak/debug.h>

using namespace oak;

Animator::Animator(uchar initialAnimID, SpriteAnimation* initialAnimation) : Component(TICK_GROUP_DEFAULT, TICK_TYPE_INTERVAL_TICK, true)
{
  this->initialAnimID = initialAnimID;
  anims[initialAnimID] = initialAnimation;
  this->curAnimID = initialAnimID;
  this->direction = ANIM_DIRECTION_RIGHT;
  initialAnimation->animator = this;
  ticker.interval = initialAnimation->getFrameDuration();
}

Animator::~Animator()
{
  for (auto it : anims)
  {
    delete it.second;
  }
  anims.clear();
}

void Animator::addAnim(const uchar animID, SpriteAnimation* animation)
{
  anims[animID] = animation;
  animation->animator = this;
}

void Animator::onTick()
{
  if (curAnimID != ANIM_INVALID)
  {
    frameIndex++;
    SpriteAnimation* curAnim = anims[curAnimID];
    bool hasAnimEnded = false;

    //if reached end of the last frame
    if (frameIndex >= curAnim->getFrameCount())
    {
      //animation doesn't loop
      if (curAnimID != initialAnimID && curAnim->getIsLooping() == false)
      {
        setAnim(initialAnimID, true);
        hasAnimEnded = true;
      }
      frameIndex = 0;
    }

    if (!hasAnimEnded)
    {
      curAnim->setFrame(frameIndex, direction);
    }
  }
}

void Animator::onRender() const
{
  if (curAnimID != ANIM_INVALID)
  {
    anims.at(curAnimID)->onRender(entity->position.x, entity->position.y);
  }
}

void Animator::setAnim(const uchar animID, const bool ignorePriority)
{
  if (curAnimID == animID)
  {
    if (hasChangedDirection)
    {
      hasChangedDirection = false;
      frameIndex = 0;
      auto curAnim = anims[curAnimID];
      curAnim->setFrame(frameIndex, direction);
      ticker.reset(curAnim->getFrameDuration());
    }
    return;
  }

  //this is a fallback to is to display nothing, which make it obvious there is a visual problem with the animation
  //if animation type doesn't exist

  auto nextAnimIt = anims.find(animID);
  if (nextAnimIt == anims.end())
  {
    curAnimID = ANIM_INVALID;
  }
  //if animation exists
  //only set the animation if the priority is equal or greater than the current animation's prioirty
  //ignorePrioirty can force an animation change regardless of the priority
  else
  {
    SpriteAnimation* curAnim = anims[curAnimID];
    SpriteAnimation* nextAnim = nextAnimIt->second;
    
    if (ignorePriority || curAnim->getPriority() <= nextAnim->getPriority())
    {
      hasChangedDirection = false;
      curAnimID = animID;
      frameIndex = 0;
      nextAnim->setFrame(frameIndex, direction);
      ticker.reset(nextAnim->getFrameDuration());
    }
  }
}

uchar Animator::getCurAnimID() const
{
  return curAnimID;
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
    setAnim(curAnimID);
  }
}
