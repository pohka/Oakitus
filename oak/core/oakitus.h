#ifndef OAKITUS_H
#define OAKITUS_H

#include "gl_window.h"

#include <vector>
#include "shader.h"
#include "entity.h"
#include "id_generator.h"
#include <string>
#include "scene.h"
#include <queue>
#include "camera.h"
#include "types.h"
#include "resources.h"

namespace oak
{

  class Oakitus
  {
    static std::vector<Entity*> entities;
    static IDGenerator* shaderIDGen;
    static Scene* curScene;
    static std::queue<uint> destroyEntIDQueue;

    public:
      static GLWindow* glWindow;
      static Camera* camera;

      static void addEntity(Entity& entity);
      static void deleteAllEnts();
      static void deleteAllEnts(std::vector<int> exceptionIDs);
      static void destroy(uint entityID);
      static void destroyEntityByID(uint entityID);
      static Entity* findEntityByID(uint id);
      static void onDestroy();
      static void onDraw();
      static void onUpdate();
      static void setScene(Scene& scene);

  };
}

#endif
