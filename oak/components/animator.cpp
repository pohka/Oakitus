#include "animator.h"

using namespace oak;

Animator::Animator()
{

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
    anims.at(curAnim)->onUpdate();
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
  }
}

uchar Animator::getCurAnimType()
{
  return curAnim;
}