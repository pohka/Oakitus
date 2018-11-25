#ifndef SCENE_H
#define SCENE_H


namespace oak
{
  class Scene
  {
    static Scene* curScene;
    static Scene* nextScene;
    

    public:
      static void swapScene();

      static Scene* getCurrentScene();
      static void  reloadScene();
      static bool isNewSceneSet();
      static void loadFirstScene(Scene& scene);
      static void setScene(Scene& scene);

      Scene();
      ~Scene();
      virtual void onLoad();
      void onUnload();
    private:

  };
}
#endif
