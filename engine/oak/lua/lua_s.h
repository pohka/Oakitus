#ifndef OAK_LUA_LOADER_H
#define OAK_LUA_LOADER_H

#include <string>
#include <lua/lua.hpp>
#include <map>
#include <oak/lua/luah_entity.h>
#include <oak/lua/luah_lua_script.h>
#include <oak/lua/luah_ability.h>

namespace oak
{
  class LuaS
  {
  public:
    //lua state
    static lua_State* state;

    //initializes lua state, functions and metatables
    static void init();

    //loads a lua file from path, files that are already loaded will not require a file read
    static void loadFile(const std::string& fileName);

    //sets the file to be called, the file must already be loaded 
    static void doFile(const std::string& fileName);

    //calls the currently set file, result=1 is the number of return values
    static void call(const int result=0);

    //closes the lua state and clears the files loaded
    static void close();

    //error log for when lua is interpreted
    static void log(const std::string& msg);


    //sets the global accessors
    static void setThisEntity(Entity* entity);
    static void setThisScript(LuaScript* script);
    static void setThisAbility(LuaAbility* ability);

    //get the global accessor for handlers
    static const LuaHLuaScript* getScriptHandler();
    static const LuaHAbility* getAbilityHandler();

    //sets the func to be called, returns false if the function does not exist
    static bool setFunc(const char* filePath, const char* className, const char* funcName);

  private:
    //registers all lua metatables and functions
    static void registerBindings(lua_State* L);

    //string content of loaded files <fileName, fileContent>
    static std::map<std::string, std::string> files;

    //fileName of the currently loaded file
    static std::string curLoadedFile;

    //global accessor handlers
    static LuaHEntity* thisEntity;
    static LuaHLuaScript* thisScript;
    static LuaHAbility* thisAbility;
  };
}

#endif