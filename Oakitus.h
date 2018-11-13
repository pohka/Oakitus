#ifndef OAKITUS_H
#define OAKITUS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLWindow.h"

#include <vector>
#include "Shader.h"
#include "Entity.h"
#include "IDGenerator.h"
#include <string>

class Oakitus
{
	
	public :
		static GLWindow* glWindow;
		static Shader* getShaderByID(unsigned int id);
		static void addShader(Shader& shader);
		static Entity* findEntityByID(unsigned int id);
		static void addEntity(Entity& entity);
		static Shader* findShaderByName(std::string name);
		static unsigned int defaultShaderID;
		static void update();
		static void draw();
		static void destroy(unsigned int entityID);
	private :
		static std::vector<Shader*> shaders;
		static std::vector<Entity*> entities;
		static IDGenerator* shaderIDGen;
		

};

#endif
