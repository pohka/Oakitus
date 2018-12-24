#include "window.h"
#include <iostream>
#include "input.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ui/ui_canvas.h>

using namespace oak;

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* Window::window = nullptr;
uint Window::viewportW;
uint Window::viewportH;
uint Window::windowW;
uint Window::windowH;
float Window::vpAspectRatio;
float Window::windowToVPRatioX;
float Window::windowToVPRatioY;
glm::mat4 Window::projectionMatrix;

float Window::worldToVPRatio;

void Window::init(
  uint viewportW,
  uint viewportH,
  uint windowW,
  uint windowH,
  const char* title,
  bool isFullscreen
)
{
  Window::viewportW = viewportW;
  Window::viewportH = viewportH;

  

  Window::vpAspectRatio = (float)viewportW / (float)viewportH;
  projectionMatrix = glm::ortho(-1.0f * vpAspectRatio, 1.0f * vpAspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

  //2 units per dimension
  float pixelsPerUnit = (float)viewportH * 0.5f;
  worldToVPRatio = 2.0f / (float)viewportH;

  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWmonitor* monitor;
  if (isFullscreen)
  {
    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    windowW = mode->width;
    windowH = mode->height;
  }
  else
  {
    monitor = NULL;
  }

  Window::windowW = windowW;
  Window::windowH = windowH;

  updateWindowToVPRatio();

  // glfw window creation
  // --------------------
  Window::window = glfwCreateWindow(windowW, windowH, title, monitor, NULL);
  if (Window::window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }

  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  int monitorWidth = mode->width;
  int monitorHeight = mode->height;

  
  int windowPosX = monitorWidth / 2 - windowW / 2;
  int windowPosY = monitorHeight / 3 - windowH / 2;

  

  glfwSetWindowPos(window, windowPosX, windowPosY);
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glfwSetCursorPosCallback(window, cursorMoved);
}

GLFWwindow* Window::getGLFWWindow()
{
  return window;
}

float Window::getAspectRatio()
{
  return vpAspectRatio;
}

uint Window::getHeight()
{
  return viewportH;
}

uint Window::getWidth()
{
  return viewportW;
}


//converts pixels to viewport units
float Window::worldToViewportCoords(float pixels)
{
  return pixels * worldToVPRatio;
}


void Window::cursorMoved(GLFWwindow* window, double xpos, double ypos)
{
  // invert y-coordinate
  Input::setMouse((float)xpos * windowToVPRatioX, ((float)Window::windowH - (float)ypos) * windowToVPRatioY);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  windowW = width;
  windowH = height;

  updateWindowToVPRatio();
  //windowToVPRatioX = (float)Window::viewportW / (float)Window::windowW;
  //windowToVPRatioY = (float)Window::viewportH / (float)Window::windowH;
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  ion::UICanvas::onWindowResize(windowToVPRatioX, windowToVPRatioY);


  glViewport(0, 0, width, height);
}

glm::vec2 Window::getWindowToVPRatio()
{
  return glm::vec2(
    windowToVPRatioX,
    windowToVPRatioY
  );
}


void Window::updateWindowToVPRatio()
{
  windowToVPRatioX = (float)Window::viewportW / (float)Window::windowW;
  windowToVPRatioY = (float)Window::viewportH / (float)Window::windowH;
}

glm::mat4& Window::getProjectionMatrix()
{
  return projectionMatrix;
}

glm::vec2 Window::getWindowUnitToPixel()
{
  return glm::vec2(
    windowW * 0.5f,
    windowH * 0.5f
  );
}

void Window::close()
{
  glfwSetWindowShouldClose(window, true);
}