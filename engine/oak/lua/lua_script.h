#ifndef LUA_SCRIPT_H
#define LUA_SCRIPT_H

#include <oak/ecs/component.h>
#include <string>
#include <lua/lua.hpp>
#include <unordered_map>
#include <oak/time/time.h>

namespace oak
{
  //key value struct to store and access different types
  struct KVData
  {
    static const char LUA_KV_TYPE_NULL = 0;
    static const char LUA_KV_TYPE_NUMBER = 1;
    static const char LUA_KV_TYPE_STRING = 2;

    std::unordered_map<std::string, float> KVNumber = {};
    std::unordered_map<std::string, std::string> KVString = {};

    //return type
    const char getType(const std::string& key) const
    {
      auto itNum = KVNumber.find(key);
      if (itNum != KVNumber.end())
      {
        return LUA_KV_TYPE_NUMBER;
      }
      else
      {
        auto itStr = KVString.find(key);
        if (itStr != KVString.end())
        {
          return LUA_KV_TYPE_STRING;
        }
      }

      return LUA_KV_TYPE_NULL;
    }

    //find and remove a KV value
    void erase(const std::string& key)
    {
      auto itNum = KVNumber.find(key);
      if (itNum != KVNumber.end())
      {
        KVNumber.erase(key);
      }
      else
      {
        auto itStr = KVString.find(key);
        if (itStr != KVString.end())
        {
          KVString.erase(key);
        }
      }
    }
  };

  struct Thinker
  {
    const char* thinkerName;
    const char* funcName;
    float nextTickTime;

    Thinker(const char* thinkerName, const char* funcName, float initialDelay) : 
      thinkerName(thinkerName),
      funcName(funcName),
      nextTickTime(Time::getGameTime() + initialDelay)
    {

    }
  };

  class LuaScript : public Component
  {
    const static std::string PATH;

    const std::string name;
    const std::string scriptFilePath;

    bool getFunc(const char* funcName);

    std::vector<Thinker> thinkers = {};

  public:

    LuaScript(const std::string& name);
    ~LuaScript();


    KVData kvdata;

    void onCreate() override;
    void onTick() override;
    void onDestroy() override;
    

    void setThink(const char* thinkerName, const char* funcName, float initialDelay = -0.0001f);
  };
}

#endif