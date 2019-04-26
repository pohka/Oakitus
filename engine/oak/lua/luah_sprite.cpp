#include <oak/lua/luah_sprite.h>
#include <iostream>
#include <oak/lua/lua_constants.h>
#include <oak/lua/lua_type.h>

using namespace oak;



LuaHSprite::LuaHSprite(Sprite* sprite)
{
  this->ptr = sprite;
}

LuaHSprite::~LuaHSprite()
{

}

void LuaHSprite::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLER_SPRITE);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getSrc); lua_setfield(L, -2, "getSrc");
  lua_pushcfunction(L, setSrc); lua_setfield(L, -2, "setSrc");
  lua_pop(L, 1);
}

//int LuaSprite::lua_new(lua_State* L)
//{
//
//  *reinterpret_cast<LuaSprite**>(lua_newuserdata(L, sizeof(LuaSprite*))) = new LuaSprite();
//}

int LuaHSprite::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaHSprite**>(lua_touserdata(L, 1));
  return 0;
}

int LuaHSprite::getSrc(lua_State* L)
{
  LuaHSprite* sprite = *reinterpret_cast<LuaHSprite**>(lua_touserdata(L, 1));
  std::string s = sprite->ptr->getSrc(); 
  lua_pushstring(L, s.c_str());
  return 1;
}

int LuaHSprite::setSrc(lua_State* L)
{
  LuaHSprite* sprite = *reinterpret_cast<LuaHSprite**>(lua_touserdata(L, 1));
  const char* src = LuaType::toString(L, 2);
  sprite->ptr->setSrc(src);
  return 0;
}