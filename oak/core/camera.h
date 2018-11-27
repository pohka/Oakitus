#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace oak
{
  class Camera
  {
    public:
	    static glm::vec3 position;
      static glm::vec3 front;
      static glm::vec3 up;
      static float fov;
      static bool isOrthographic;

      static void init(glm::vec3 position, glm::vec3 front, glm::vec3 up, float fov, bool isOrthographic);
      static glm::vec2 cursorToWorld2D();
      static bool getIsOrthographic();
      static glm::vec3 viewportToWorldCoor(float vpPosX, float vpPosY);
      static glm::vec3 getNormalizedPos();
  };
}
#endif