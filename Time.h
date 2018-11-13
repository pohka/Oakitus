#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

class Time
{
	public:
		static float timeScale;
		static float deltaTime;

		static void init()
		{
			lastFrame = glfwGetTime();
		}
		
		static void calcDeltaTime()
		{
			float currentFrame = (float)glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			deltaTime = (float)(1 * deltaTime);
		}
		

	private:
		static float lastFrame;
		static float m_deltaTime;
};

#endif
