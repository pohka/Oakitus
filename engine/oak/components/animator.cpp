#include "animator.h"
#include <oak/oak_def.h>
#include <oak/ecs/entity.h>

using namespace oak;

Animator::Animator() : 
  Component(
    Reflect::ANIMATOR,
    Component::TickGroup::DEFAULT,
    TickType::INTERVAL_TICK,
    true
  )
{
 // this->initialAnimID = initialAnimID;
 // anims[initialAnimID] = initialAnimation;
  //this->curAnimID = initialAnimID;
  this->direction = AnimDirection::RIGHT;
  //initialAnimation->animator = this;
  //ticker.interval = initialAnimation->getFrameDuration();
}

Animator::~Animator()
{
  for (auto it : anims)
  {
    delete it.second;
  }
  anims.clear();
}

void Animator::addAnim(uchar animID, SpriteAnimation* animation)
{
  anims[animID] = animation;
  animation->animator = this;
}

void Animator::onTick()
{
  if (curAnimID != ANIM_NULL)
  {
    frameIndex++;
    SpriteAnimation* curAnim = anims[curAnimID];
    bool hasAnimEnded = false;

    //if reached end of the last frame
    if (frameIndex >= curAnim->getFrameCount())
    {
      //animation doesn't loop
      if (curAnimID != ANIM_IDLE && curAnim->getIsLooping() == false)
      {
        setAnim(ANIM_IDLE, true);
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
  if (curAnimID != ANIM_NULL)
  {
    glm::vec3 pos = entity->transform->position();
    anims.at(curAnimID)->onRender(pos.x, pos.y);
  }
}

void Animator::setAnim(uchar animID, bool ignorePriority)
{
  //ignore null
  if (animID == ANIM_NULL)
  {
    return;
  }

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
    curAnimID = ANIM_NULL;
  }
  //if animation exists
  //only set the animation if the priority is equal or greater than the current animation's prioirty
  //ignorePrioirty can force an animation change regardless of the priority
  else
  {
    SpriteAnimation* curAnim = nullptr;
    if (curAnimID != ANIM_NULL)
    {
      curAnim = anims[curAnimID];
    }
    SpriteAnimation* nextAnim = nextAnimIt->second;

    if (curAnimID == ANIM_NULL || ignorePriority || curAnim->getPriority() <= nextAnim->getPriority())
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

AnimDirection Animator::getDirection() const
{
  return direction;
}

void Animator::setDirection(AnimDirection direction)
{
  if (this->direction != direction)
  {
    hasChangedDirection = true;
    this->direction = direction;
    setAnim(curAnimID);
  }
}
