#ifndef OAKITUS_H
#define OAKITUS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLWindow.h"

#include <vector>
#include "shader_s.h"
#include "Entity.h"

class Oakitus
{
	
	public :
		Oakitus();
		~Oakitus();
		std::vector<Shader*> shaders;
		std::vector<Entity*> entities;
	private :
		static GLWindow* glWindow;
		

};

#endif
