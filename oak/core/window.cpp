#include "window.h"
#include <iostream>
#include "input.h"

using namespace oak;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* Window::window = nullptr;
uint Window::screenW;
uint Window::screenH;
float Window::worldToVPRatio;

void Window::init(uint screenW, uint screenH, const char* title)
{
  Window::screenW = screenW;
  Window::screenH = screenH;

  //2 units per dimension
  float pixelsPerUnit = (float)screenH * 0.5f;
  worldToVPRatio = 1 / pixelsPerUnit;

  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw window creation
  // --------------------
  Window::window = glfwCreateWindow(screenW, screenH, title, NULL, NULL);
  if (Window::window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  glEnable(GL_BLEND);
  glfwSetCursorPosCallback(window, cursorMoved);
}

GLFWwindow* Window::getGLFWWindow()
{
  return window;
}

float Window::getAspectRatio()
{
  return (float)screenW / (float)screenH;
}

uint Window::getHeight()
{
  return screenH;
}

uint Window::getWidth()
{
  return screenW;
}

//converts pixels to viewport units
float Window::worldToViewportCoords(float pixels)
{
  return pixels * worldToVPRatio;
}


void Window::cursorMoved(GLFWwindow* window, double xpos, double ypos)
{
  // invert y-coordinate
  Input::setMouse((float)xpos, (float)Window::getHeight() - (float)ypos);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
