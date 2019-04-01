#include "lua_scene.h"
#include <lua/lua.hpp>
#include <oak/debug.h>
#include <oak/oak.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <locale>

using namespace oak;
using json = nlohmann::json;

LuaScene* LuaScene::scene = nullptr;

LuaScene::LuaScene(std::string path) : Scene()
{
  this->path = path;
  std::ifstream i(path + "file.json");
  i >> data;
  if (data != nullptr)
  {
    dataLoaded = true;

    //reading precache asset names
    if (data["precache"] != nullptr)
    {
      //textures
      if (data["precache"]["textures"] != nullptr)
      {
        for (unsigned int i = 0; i < data["precache"]["textures"].size(); i++)
        {
          if (data["precache"]["textures"][i].is_string())
          {
            precache.textures.push_back(data["precache"]["textures"][i]);
          }
        }
      }
      //shaders
      if (data["precache"]["shaders"] != nullptr)
      {
        for (unsigned int i = 0; i < data["precache"]["shaders"].size(); i++)
        {
          if (data["precache"]["shaders"][i].is_string())
          {
            precache.shaders.push_back(data["precache"]["shaders"][i]);
          }
        }
      }
      //fonts
      if (data["precache"]["fonts"] != nullptr)
      {
        for (unsigned int i = 0; i < data["precache"]["fonts"].size(); i++)
        {
          if (data["precache"]["fonts"][i].is_string())
          {
            precache.fonts.push_back(data["precache"]["fonts"][i]);
          }
        }
      }
    }

    //todo
    if (data["commands"] != nullptr)
    {
      for (unsigned int i = 0; i < data["commands"].size(); i++)
      {
        if (data["commands"][i].is_string())
        {
          
        }
      }
    }
  }

  LuaScene::scene = this;
}

void LuaScene::onLoad()
{
  //std::string initScript = path + "scripts/main.lua";
  L = luaL_newstate();
  luaL_openlibs(L);
  lua_register(L, "create", LuaScene::lua_create);
  lua_register(L, "addCommand", LuaScene::lua_addCommand);

  //possibly change this in future to: scripts/main.lua
  //right now the VS root path for lua is not correct
  //therefore it cant find the scripts when using require() in lua
  //if you open the exe directly with the path: "scripts/main.lua", it will work but not in VS runtime
  std::string initScript = "../Release/scripts/main.lua";
  luaL_loadfile(L, initScript.c_str());

  //no error checking and will cause crash if there is a lua error
  //lua_call(L, 0, 0);

  //lua_pcall returns errors
  if (lua_pcall(L, 0, 0, 0) != 0)
  {
    std::cout << "|--LUA_ERROR--|" << " lua_pcall - " << lua_tostring(L, -1) << std::endl;
  }
  lua_close(L);
}

void LuaScene::logError(lua_State* L, std::string msg)
{
  lua_Debug ar;
  lua_getstack(L, 1, &ar);
  lua_getinfo(L, "nSl", &ar);
  int line = ar.currentline;

  std::cout << "|--LUA_ERROR--| line " << line << " - " << msg << std::endl;
}

int LuaScene::lua_create(lua_State *L)
{
  float x, y;

  if (lua_gettop(L) == 1)
  {
    x = 0.0f;
    y = 0.0f;
  }
  else if (lua_gettop(L) == 3)
  {
    x = (float)luaL_checknumber(L, 2);
    y = (float)luaL_checknumber(L, 3);
  }
  else
  {
    logError(L, "invalid number of arguments");
    return 0;
  }

  std::string name = lua_tostring(L, 1);
  

  if (LuaScene::scene->dataLoaded == false)
  {
    std::string s = "Could not find entity: '" + name + "'";
    logError(L, s);
  }
  else
  {
    json entData = LuaScene::scene->data["0"][name];
    if (entData != nullptr)
    {
      Entity* ent = new Entity();
      ent->name = name;
      for (uint i = 0; i < entData.size(); i++)
      {
        std::string className = entData[i]["class"];

        //sprite
        if (className == "sprite")
        {
          std::string src = entData[i]["src"];
          float w = entData[i]["w"];
          float h = entData[i]["h"];
          ent->addComponent(new Sprite(src, w, h));
        }
        //collision rect
        else if (className == "collision_rect")
        {
          float offsetX = entData[i]["offsetX"];
          float offsetY = entData[i]["offsetY"];
          float w = entData[i]["w"];
          float h = entData[i]["h"];
          ent->addCollision(new CollisionRect(offsetX, offsetY, w, h));
        }
        //collision circle
        else if (className == "collision_circle")
        {
          float offsetX = entData[i]["offsetX"];
          float offsetY = entData[i]["offsetY"];
          float radius = entData[i]["radius"];
          ent->addCollision(new CollisionCircle(radius, offsetX, offsetY));
        }
        //rigid body 2d
        else if (className == "rigidbody2d")
        {
          bool isStatic = entData[i]["isStatic"];
          ent->addComponent(new RigidBody2D(isStatic));
        }
      }
      ent->create(x, y);

      lua_pushnumber(L, ent->getID());
      return 1;
    }
  }

  lua_pushnumber(L, -1);
  return 1;
}

int LuaScene::lua_addCommand(lua_State *L)
{
  if (lua_gettop(L) != 2)
  {
    LOG << "lua_gettop(L):" << lua_gettop(L);
    logError(L, "invalid number of arguments, expected 2");
  }
  else
  {
    std::string name = lua_tostring(L, 1);
    int playerID = (int)luaL_checknumber(L, 2);

    Player* player = PlayerResource::getPlayer(playerID);
    if (player != nullptr)
    {
      LOG << "added command success";
      player->lua_addCommand(name);
    }
    else
    {
      std::string s = "playerID not found: " + playerID;
      logError(L, s);
    }
  }

  return 0;
}
