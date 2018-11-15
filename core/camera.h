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
	    glm::vec3 position;
	    glm::vec3 front;
	    glm::vec3 up;
	    float fov;

	    Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float fov);
	    ~Camera();
	    glm::vec3 cursorToWorld2D();
	    glm::vec3 viewportToWorldCoor(float vpPosX, float vpPosY);
  };
}
#endif