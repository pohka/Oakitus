#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

class Time
{
	static float lastFrame;
	static float m_deltaTime;

	public:
		static float timeScale;
		static float deltaTime;

		
		
		static void calcDeltaTime()
		{
			float currentFrame = (float)glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			deltaTime = (float)(1 * deltaTime);
		}
		
		static void init()
		{
			lastFrame = (float)glfwGetTime();
		}
};

#endif
