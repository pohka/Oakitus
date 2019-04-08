#include <oak/lua/lua_sprite.h>
#include <iostream>
#include <oak/lua/lua_constants.h>

using namespace oak;



LuaSprite::LuaSprite(Sprite* sprite)
{
  this->ptr = sprite;
}

LuaSprite::~LuaSprite()
{

}

void LuaSprite::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLE_SPRITE);
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

int LuaSprite::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaSprite**>(lua_touserdata(L, 1));
  return 0;
}

int LuaSprite::getSrc(lua_State* L)
{
  LuaSprite* sprite = *reinterpret_cast<LuaSprite**>(lua_touserdata(L, 1));
  lua_pushstring(L, sprite->ptr->getSrc().c_str());
  return 1;
}

int LuaSprite::setSrc(lua_State* L)
{
  LuaSprite* sprite = *reinterpret_cast<LuaSprite**>(lua_touserdata(L, 1));
  const char* src = luaL_checkstring(L, 2);
  sprite->ptr->setSrc(src);
  return 0;
}