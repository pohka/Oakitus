#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <core/entity.h>
#include <core/types.h>

namespace game
{
  namespace prefab
  {
    class CameraController : public oak::Entity
    {
      uint targetEntityID;
      bool hasTarget;

      public:
        CameraController();
        ~CameraController();

        

        void followTarget(uint entityID);

      protected:
        void onLateUpdate() override;
    };
  }
}
#endif