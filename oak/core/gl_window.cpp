#include "gl_window.h"
#include <iostream>
#include "input.h"

using namespace oak;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


GLWindow::GLWindow(uint windowW, uint windowH, const char* title)
{
  this->windowW = windowW;
  this->windowH = windowH;
  this->viewportW = 960;
  this->viewportH = 540;
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw window creation
  // --------------------
  this->window = glfwCreateWindow(windowW, windowH, title, NULL, NULL);
  if (this->window == NULL)
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
}

GLWindow::~GLWindow()
{

}

GLFWwindow* GLWindow::getGLFWWindow()
{
  return this->window;
}

float GLWindow::getAspectRatio()
{
  return (float)viewportW / (float)viewportH;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
