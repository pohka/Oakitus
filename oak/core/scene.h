#ifndef SCENE_H
#define SCENE_H


namespace oak
{
  class Scene
  {
    public:
      Scene();
      ~Scene();
      virtual void onLoad();
      void onUnload();
    private:

  };
}
#endif
