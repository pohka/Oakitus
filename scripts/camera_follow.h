#ifndef CAMERA_FOLLOW_H
#define CAMERA_FOLLOW_H

#include <core/script.h>
#include <core/camera.h>

namespace game
{
  class CameraFollow : public oak::Script
  {
  public:
    CameraFollow();
    ~CameraFollow();
    void init() override;
    void onUpdate() override;
  };
}
#endif