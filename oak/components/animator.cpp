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
      setAnim(baseAnim);
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

void Animator::setAnim(const uchar animType)
{
  //check if animation type exist
  if (anims.find(animType) == anims.end())
  {
    curAnim = 0;
  }
  else
  {
    curAnim = animType;
    anims.at(curAnim)->reset();
  }
}

uchar Animator::getCurAnimType()
{
  return curAnim;
}