#include <oak/lua/lua_animator.h>
#include <oak/lua/lua_constants.h>

using namespace oak;

LuaAnimator::LuaAnimator(Animator* animator)
{
  ptr = animator;
}
LuaAnimator::~LuaAnimator()
{

}

void LuaAnimator::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLE_ANIMATOR);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, setAnim); lua_setfield(L, -2, "setAnim");
  lua_pushcfunction(L, getCurAnimID); lua_setfield(L, -2, "getCurAnimID");
  lua_pushcfunction(L, getDirection); lua_setfield(L, -2, "getDirection");
  lua_pushcfunction(L, setDirection); lua_setfield(L, -2, "setDirection");
  lua_pop(L, 1);
}

int LuaAnimator::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaAnimator**>(lua_touserdata(L, 1));
  return 0;
}

int LuaAnimator::setAnim(lua_State* L)
{
  LuaAnimator* animatorH = *reinterpret_cast<LuaAnimator**>(lua_touserdata(L, 1));
  int animID = luaL_checkinteger(L, 2);
  bool ignorePriority = false;

  if (lua_isboolean(L, 3))
  {
    ignorePriority = lua_toboolean(L, 3);
  }
  animatorH->ptr->setAnim(animID, ignorePriority);

  return 0;
}

int LuaAnimator::getCurAnimID(lua_State* L)
{
  LuaAnimator* animatorH = *reinterpret_cast<LuaAnimator**>(lua_touserdata(L, 1));
  lua_pushinteger(L, animatorH->ptr->getCurAnimID());
  return 1;
}

int LuaAnimator::getDirection(lua_State* L)
{
  LuaAnimator* animatorH = *reinterpret_cast<LuaAnimator**>(lua_touserdata(L, 1));
  lua_pushinteger(L, animatorH->ptr->getDirection());
  return 1;
}

int LuaAnimator::setDirection(lua_State* L)
{
  LuaAnimator* animatorH = *reinterpret_cast<LuaAnimator**>(lua_touserdata(L, 1));
  lua_pushinteger(L, animatorH->ptr->getCurAnimID());
  unsigned char direction = (unsigned char)luaL_checkinteger(L, 2);
  animatorH->ptr->setDirection(direction);
  return 0;
}