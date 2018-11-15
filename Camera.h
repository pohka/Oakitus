#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera
{
	public:
		vec3 position;
		vec3 front;
		vec3 up;
		float fov;

		Camera(vec3 position, vec3 front, vec3 up, float fov);
		~Camera();
		vec3 cursorToWorld2D();
		vec3 viewportToWorldCoor(float vpPosX, float vpPosY);
		
};
#endif