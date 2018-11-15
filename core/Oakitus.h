#ifndef OAKITUS_H
#define OAKITUS_H

#include "GLWindow.h"

#include <vector>
#include "Shader.h"
#include "Entity.h"
#include "IDGenerator.h"
#include <string>
#include "Scene.h"
#include <queue>
#include "Camera.h"

namespace oak
{
  class Oakitus
  {
    static std::vector<Shader*> shaders;
    static std::vector<Entity*> entities;
    static IDGenerator* shaderIDGen;
    static Scene* curScene;
    static std::queue<unsigned int> destroyEntIDQueue;

    public:
      static GLWindow* glWindow;
      static Camera* camera;
      static unsigned int defaultShaderID;

      static void addEntity(Entity& entity);
      static void addShader(Shader& shader);
      static void deleteAllEnts();
      static void deleteAllEnts(std::vector<int> exceptionIDs);
      static void destroy(unsigned int entityID);
      static void destroyEntityByID(unsigned int entityID);
      static Entity* findEntityByID(unsigned int id);
      static Shader* findShaderByID(unsigned int id);
      static Shader* findShaderByName(std::string name);
      static void onDestroy();
      static void onDraw();
      static void onUpdate();
      static void setScene(Scene& scene);

  };
}

#endif