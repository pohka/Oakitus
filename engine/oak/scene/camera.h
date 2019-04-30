#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace oak
{
  //The Camera, there is only one
  class Camera
  {
    friend class Oakitus;

    public:
	    static glm::vec3 position; //World position of the Camera
      static glm::vec3 front; //Front direction
      static glm::vec3 up; //Up direction
      static float fov; //Field of view
      static bool isOrthographic; //If Camera is in orthographic mode

      
      //Converts the current cursor position to world coordinated in 2D
      static glm::vec2 cursorToWorld2D();

      //Returns true if in orthographic mode
      static bool getIsOrthographic();

      //
      static glm::vec3 viewportToWorldCoor(float vpPosX, float vpPosY);

      //Returns the normalized position in viewport coordinates
      static glm::vec3 getNormalizedPos();


    protected:
      //initalize the camera
      static void init(glm::vec3 position, glm::vec3 front, glm::vec3 up, float fov, bool isOrthographic);
  };
}
#endif