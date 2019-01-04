#include "wall_test.h"
#include <oak/oak.h>

using namespace game;
using namespace oak;

WallTest::WallTest(float w, float h)
{
  addComponent(new Sprite("default.png", w, h));
  addCollision(new CollisionRect(0.0f, 0.0f, w, h));
  addRigidBody(new RigidBody2D(true));
}