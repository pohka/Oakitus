#ifndef OAKITUS_H
#define OAKITUS_H

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

#include "GLWindow.h"

#include <vector>
#include "Shader.h"
#include "Entity.h"
#include "IDGenerator.h"
#include <string>
#include "Scene.h"
#include <queue>
#include "Camera.h"


class Oakitus
{
	public :
		static GLWindow* glWindow;
		static Camera* camera;

		static Shader* getShaderByID(unsigned int id);
		static void addShader(Shader& shader);
		static Entity* findEntityByID(unsigned int id);
		static void addEntity(Entity& entity);
		static Shader* findShaderByName(std::string name);
		static unsigned int defaultShaderID;
		static void onUpdate();
		static void onDraw();
		static void destroy(unsigned int entityID);
		static void setScene(Scene& scene);
		static void destroyEntityByID(unsigned int entityID);
		static void onDestroy();
		static void deleteAllEnts();
		static void deleteAllEnts(std::vector<int> exceptionIDs);
	private :
		static std::vector<Shader*> shaders;
		static std::vector<Entity*> entities;
		static IDGenerator* shaderIDGen;
		static Scene* curScene;
		static std::queue<unsigned int> destroyEntIDQueue;
		
};

#endif
