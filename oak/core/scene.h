#ifndef SCENE_H
#define SCENE_H


namespace oak
{
  ///<summary>Handling of loading and unload Entitys and resources when changing scenes</summary>
  class Scene
  {
    friend class Oakitus;

    static Scene* curScene; ///<summary>Current scene</summary>
    static Scene* nextScene; ///<summary>Pointer for when the next scene is queued</summary>
    

    public:
      ///<summary>Returns the current scene</summary>
      static Scene* getCurrentScene();

      ///<summary>Reloads the current scene</summary>
      static void  reloadScene();

      ///<summary>Returns true if the next scene has been set</summary>
      static bool isNextSceneSet();

      ///<summary>Should be called once to load the first scene in Oakitus::load()</summary>
      static void loadFirstScene(Scene& scene);

      ///<summary>Sets and swaps out the next scene</summary>
      static void setNextScene(Scene& scene);

      Scene();
      ~Scene();

      ///<summary>Loads the this scene</summary>
      virtual void onLoad();

      ///<summary>Unloads this scene</summary>
      void onUnload();

    private:
      ///<summary>swaps out the next scene</summary>
      static void swapScene();
  };
}
#endif
