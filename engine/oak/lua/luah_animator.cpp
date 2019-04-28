#include <oak/lua/luah_animator.h>
#include <oak/lua/lua_constants.h>
#include <iostream>
#include <oak/lua/lua_type.h>

using namespace oak;

LuaHAnimator::LuaHAnimator(Animator* animator)
{
  ptr = animator;
}
LuaHAnimator::~LuaHAnimator()
{

}

void LuaHAnimator::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLER_ANIMATOR);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, setAnim); lua_setfield(L, -2, "setAnim");
  lua_pushcfunction(L, getCurAnimID); lua_setfield(L, -2, "getCurAnimID");
  lua_pushcfunction(L, getDirection); lua_setfield(L, -2, "getDirection");
  lua_pushcfunction(L, setDirection); lua_setfield(L, -2, "setDirection");
  lua_pop(L, 1);
}

int LuaHAnimator::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaHAnimator**>(lua_touserdata(L, 1));
  return 0;
}

int LuaHAnimator::setAnim(lua_State* L)
{
  LuaHAnimator* animatorH = *reinterpret_cast<LuaHAnimator**>(lua_touserdata(L, 1));
  int animID = LuaType::toInt(L, 2);
  bool ignorePriority = false;

  if (lua_isboolean(L, 3))
  {
    ignorePriority = lua_toboolean(L, 3);
  }
  animatorH->ptr->setAnim(animID, ignorePriority);

  return 0;
}

int LuaHAnimator::getCurAnimID(lua_State* L)
{
  LuaHAnimator* animatorH = *reinterpret_cast<LuaHAnimator**>(lua_touserdata(L, 1));
  lua_pushinteger(L, animatorH->ptr->getCurAnimID());
  return 1;
}

int LuaHAnimator::getDirection(lua_State* L)
{
  LuaHAnimator* animatorH = *reinterpret_cast<LuaHAnimator**>(lua_touserdata(L, 1));
  lua_pushinteger(L, static_cast<int>(animatorH->ptr->getDirection()));
  return 1;
}

int LuaHAnimator::setDirection(lua_State* L)
{
  LuaHAnimator* animatorH = *reinterpret_cast<LuaHAnimator**>(lua_touserdata(L, 1));
  lua_pushinteger(L, animatorH->ptr->getCurAnimID());
  uchar direction = LuaType::toUChar(L, 2);
  animatorH->ptr->setDirection(static_cast<AnimDirection>(direction));
  return 0;
}