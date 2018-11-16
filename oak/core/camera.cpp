#include "camera.h"
#include "oakitus.h"
#include "input.h"
#include "ray.h"

using namespace glm;
using namespace oak;

Camera::Camera(vec3 position, vec3 front, vec3 up, float fov)
{
  this->position = position;
  this->front = front;
  this->up = up;
  this->fov = fov;
}

Camera::~Camera() {}

vec3 Camera::cursorToWorld2D()
{
  float screenH = 800;
  glm::vec3 rayWorld = Oakitus::camera->viewportToWorldCoor(Input::mousePos->x, Input::mousePos->y);
  Ray* ray = new Ray(Oakitus::camera->position, rayWorld);

  glm::vec3 point = ray->planeIntersectPoint(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0));
  delete ray;
  return point;
}

vec3 Camera::viewportToWorldCoor(float vpPosX, float vpPosY)
{
  float screenH = 600, screenW = 800;
  glm::mat4 viewMatrix = glm::lookAt(
    Oakitus::camera->position,
    Oakitus::camera->front,
    Oakitus::camera->up
  );
  glm::mat4 projectionMatrix = glm::perspective(
    glm::radians(Oakitus::camera->fov), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
    screenW / screenH,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
    0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
    100.0f             // Far clipping plane. Keep as little as possible.
  );

  //normalize viewport coordinates so its a value between -1 and 1
  glm::vec2 nCursor = glm::vec2(
    ((2.0f * vpPosX) / screenW) - 1.0f,
    ((2.0f * vpPosY) / screenH) - 1.0f
  );

  glm::mat4 inverse = glm::inverse(projectionMatrix * viewMatrix);
  glm::vec4 rayClip = glm::vec4(nCursor.x, nCursor.y, -1, 1);


  glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
  rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);
  glm::vec3 rayWorld = (glm::inverse(viewMatrix) * rayEye);
  rayWorld = glm::normalize(rayWorld);
  return rayWorld;
}

