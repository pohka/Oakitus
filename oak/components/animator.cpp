#include "animator.h"

using namespace oak;

Animator::Animator(uchar baseAnimType, SpriteAnimation* baseAnimation)
{
  this->baseAnim = baseAnimType;
  anims[baseAnimType] = baseAnimation;
  this->curAnim = baseAnimType;
}

Animator::~Animator()
{

}

void Animator::addAnim(const uchar animType, SpriteAnimation* animation)
{
  anims[animType] = animation;
}

void Animator::onUpdate()
{
  if (curAnim > 0)
  {
    bool hasEnded = anims.at(curAnim)->onUpdate();
    if (hasEnded && curAnim != baseAnim)
    {
      setAnim(baseAnim, true);
    }
  }
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

  //check if animation type exist
  if (anims.find(animType) == anims.end())
  {
    curAnim = 0;
  }
  //if animation exists
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
