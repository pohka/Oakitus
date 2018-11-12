#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>



class GLWindow {
	public :
		GLWindow(unsigned int screenW, unsigned int screenH, const char* title);
		~GLWindow();
		GLFWwindow* getGLFWWindow();
	private :
		GLFWwindow* window;
};

#endif
