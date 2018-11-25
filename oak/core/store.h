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
#include "types.h"
#include "resources.h"

namespace oak
{

  class Store
  {
    
    static Scene* curScene;
    static Scene* nextScene;
    
    


    public:

      
      
      //static void destroy(uint entityID);
      
      static Scene* getCurrentScene();
      static void  reloadScene();
      static bool isNewSceneSet();
      static void loadFirstScene(Scene& scene);
      //static void onDestroy();
      //static void onDraw();
      static void onSceneChange();
      //static void onUpdate();
      static void setScene(Scene& scene);
      
      

  };
}

#endif
