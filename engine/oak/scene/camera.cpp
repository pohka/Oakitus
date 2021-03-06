#include "camera.h"
#include <oak/input/input.h>
#include <oak/old/ray.h>
#include <oak/window/window.h>

using namespace glm;
using namespace oak;

glm::vec3 Camera::position;
glm::vec3 Camera::front;
glm::vec3 Camera::up;
float Camera::fov;
bool Camera::isOrthographic;

void Camera::init(vec3 position, vec3 front, vec3 up, float fov, bool isOrthographic)
{
  Camera::position = position;
  Camera::front = front;
  Camera::up = up;
  Camera::fov = fov;
  Camera::isOrthographic = isOrthographic;
}


vec3 Camera::getNormalizedPos()
{
  return vec3(
    Window::worldToViewportCoords(position.x),
    Window::worldToViewportCoords(position.y),
    position.z
  );
}

vec2 Camera::cursorToWorld2D()
{
  if (isOrthographic)
  {
    float screenW = static_cast<float>(Window::getWidth());
    float screenH = static_cast<float>(Window::getHeight());

    float halfW = screenW / 2.0f;
    float halfH = screenH / 2.0f;

    //cursor pixels offset from center of viewport
    glm::vec2 cursorOffset = glm::vec2(
      Input::mousePos.x - halfW,
      Input::mousePos.y - halfH
    );

    return glm::vec2(
      cursorOffset.x + position.x,
      cursorOffset.y + position.y
    );
  }
  else
  {
    glm::vec3 rayWorld = Camera::viewportToWorldCoor(Input::mousePos.x, Input::mousePos.y);
    Ray* ray = new Ray(Camera::position, rayWorld);

    glm::vec3 point = ray->planeIntersectPoint(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0));
    delete ray;
    return point;
  }
}

bool Camera::getIsOrthographic()
{
  return isOrthographic;
}

//When using perspective view this function converts a viewport position to a world, so you can project a point into world space.
vec3 Camera::viewportToWorldCoor(float vpPosX, float vpPosY)
{
  float screenW = static_cast<float>(Window::getWidth());
  float screenH = static_cast<float>(Window::getHeight());

  glm::mat4 viewMatrix = glm::lookAt(
    position,
    front,
    up
  );
  glm::mat4 projectionMatrix = glm::perspective(
    glm::radians(fov), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90� (extra wide) and 30� (quite zoomed in)
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

