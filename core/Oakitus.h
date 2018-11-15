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
#include "Types.h"

namespace oak
{

  class Oakitus
  {
    static std::vector<Shader*> shaders;
    static std::vector<Entity*> entities;
    static IDGenerator* shaderIDGen;
    static Scene* curScene;
    static std::queue<uint> destroyEntIDQueue;

    public:
      static GLWindow* glWindow;
      static Camera* camera;
      static uint defaultShaderID;

      static void addEntity(Entity& entity);
      static void addShader(Shader& shader);
      static void deleteAllEnts();
      static void deleteAllEnts(std::vector<int> exceptionIDs);
      static void destroy(uint entityID);
      static void destroyEntityByID(uint entityID);
      static Entity* findEntityByID(uint id);
      static Shader* findShaderByID(uint id);
      static Shader* findShaderByName(std::string name);
      static void onDestroy();
      static void onDraw();
      static void onUpdate();
      static void setScene(Scene& scene);

  };
}

#endif
