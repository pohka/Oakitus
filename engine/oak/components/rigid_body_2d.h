#pragma once
#ifndef RIGID_BODY_2D_H
#define RIGID_BODY_2D_H

#include <oak/components/base_rigid_body.h>

namespace oak
{
  class RigidBody2D : public BaseRigidBody
  {
    glm::vec2 lastPos;

  public:
    bool isStatic;

    RigidBody2D(bool isStatic);
    ~RigidBody2D();
    

    //void onUpdate() override;
  };
}

#endif