#include <oak/lua/lua_script_handle.h>
#include <oak/lua/lua_constants.h>
#include <oak/lua/lua_s.h>

using namespace oak;


LuaScriptHandle::LuaScriptHandle(LuaScript* script)
{
  this->script = script;
}

LuaScriptHandle::~LuaScriptHandle()
{

}

void LuaScriptHandle::set(LuaScript* script)
{
  this->script = script;
}

void LuaScriptHandle::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLE_SCRIPT);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getKV); lua_setfield(L, -2, "getKV");
  lua_pushcfunction(L, setKV); lua_setfield(L, -2, "setKV");
  lua_pop(L, 1);
}

//getKV(type,key)
int LuaScriptHandle::getKV(lua_State* L)
{
  int res = 0;
  LuaScriptHandle* scriptH = *reinterpret_cast<LuaScriptHandle**>(luaL_checkudata(L, 1, LUA_HANDLE_SCRIPT));

  std::string key = luaL_checkstring(L, 2);

  //finds the type of the value for the key
  char type = scriptH->script->kvdata.getType(key); 

  KVData& kvdata = scriptH->script->kvdata;
  
  switch (type)
  {
    case KVData::LUA_KV_TYPE_NUMBER:
    {
      lua_pushnumber(L, kvdata.KVNumber[key]);
      res = 1;
      break;
    }
    case KVData::LUA_KV_TYPE_STRING:
    {
      lua_pushstring(L, kvdata.KVString[key].c_str());
      res = 1;
      break;
    }
    default:
    {
      //error, invalid type
      LuaS::log("invalid type for KV value");
    }
  }
  return res;
}

//setKV(key,val)
int LuaScriptHandle::setKV(lua_State* L)
{
  LuaScriptHandle* scriptH = *reinterpret_cast<LuaScriptHandle**>(luaL_checkudata(L, 1, LUA_HANDLE_SCRIPT));
  KVData& kvdata = scriptH->script->kvdata;
  

  std::string key = luaL_checkstring(L, 2);
  int type = lua_type(L, 3);

  int curType = kvdata.getType(key);

  switch (type)
  {
    case LUA_TNUMBER :
    {
      //if changing type
      if (curType != KVData::LUA_KV_TYPE_NULL || curType != KVData::LUA_KV_TYPE_NUMBER)
      {
        kvdata.erase(key);
        kvdata.KVNumber[key] = lua_tonumber(L, 3);
      }
      break;
    }
    case LUA_TSTRING :
    {
      //if changing type
      if (curType != KVData::LUA_KV_TYPE_NULL || curType != KVData::LUA_KV_TYPE_STRING)
      {
        kvdata.erase(key);
      }
      kvdata.KVString[key] = lua_tostring(L, 3);
      break;
    }
    default :
    {
      //error, invalid type
      LuaS::log("invalid type for KV value");
    }
  }
}

int LuaScriptHandle::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaScriptHandle**>(luaL_checkudata(L, 1, LUA_HANDLE_SCRIPT));
  return 0;
}

int LuaScriptHandle::setThink(lua_State* L)
{
  const char* thinkerName;
  const char* funcName;
  float initalDelay = 0.0001f;
  LuaScript* script = LuaS::getScriptHandle()->script;

  if (lua_gettop(L) == 2)
  {
    const char* thinkerName = luaL_checkstring(L, 1);
    const char* funcName = luaL_checkstring(L, 2);
    script->setThink(thinkerName, funcName);
  }
  else if (lua_gettop(L) == 3)
  {
    const char* thinkerName = luaL_checkstring(L, 1);
    const char* funcName = luaL_checkstring(L, 2);
    float initialDelay = (float)luaL_checknumber(L, 3);
    script->setThink(thinkerName, funcName, initialDelay);
  }
  else
  {
    LuaS::log("invalid number of arguments expected 2 or 3 arguments. e.g. setThinker(thinkerName, funcName, initalDelay)");
  }
 
  return 0;
}