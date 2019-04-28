#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace oak
{
  ///<summary>The Camera, there is only one</summary>
  class Camera
  {
    friend class Oakitus;

    public:
	    static glm::vec3 position; ///<summary>World position of the Camera</summary>
      static glm::vec3 front; ///<summary>Front direction</summary>
      static glm::vec3 up; ///<summary>Up direction</summary>
      static float fov; ///<summary>Field of view</summary>
      static bool isOrthographic; ///<summary>If Camera is in orthographic mode</summary>

      
      ///<summary>Converts the current cursor position to world coordinated in 2D</summary>
      static glm::vec2 cursorToWorld2D();

      ///<summary>Returns true if in orthographic mode</summary>
      static bool getIsOrthographic();

      ///<summary></summary>
      static glm::vec3 viewportToWorldCoor(float vpPosX, float vpPosY);

      ///<summary>Returns the normalized position in viewport coordinates</summary>
      static glm::vec3 getNormalizedPos();


    protected:
      ///<summary>initalize the camera</summary>
      static void init(glm::vec3 position, glm::vec3 front, glm::vec3 up, float fov, bool isOrthographic);
  };
}
#endif