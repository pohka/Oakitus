#ifndef Store_H
#define Store_H

//#include "window.h"

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

  class Store
  {
    static std::vector<Entity*> entitys;
    static Scene* curScene;
    static Scene* nextScene;
    static std::queue<uint> destroyEntIDQueue;
    


    public:
      static Camera* camera;

      static void addEntity(Entity& entity);
      static void deleteAllEntitys();
      static void deleteAllNonGlobalEntitys();
      static void destroy(uint entityID);
      static void destroyEntityByID(uint entityID);
      static Entity* findEntityByID(uint id);
      static Entity* findEntityByName(std::string name);
      static std::vector<Entity*> getGlobalEntitys();
      static Scene* getCurrentScene();
      static void  reloadScene();
      static bool isNewSceneSet();
      static void loadFirstScene(Scene& scene);
      static void onDestroy();
      static void onDraw();
      static void onSceneChange();
      static void onUpdate();
      static void setScene(Scene& scene);
      
      

  };
}

#endif
