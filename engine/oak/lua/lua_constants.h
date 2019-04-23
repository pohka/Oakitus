#ifndef LUA_CONSTANTS_H
#define LUA_CONSTANTS_H

namespace oak
{
  //global accessable tables
  static const char* LUA_GAME = "Game";
  static const char* LUA_VECTOR = "Vector";
  static const char* LUA_INPUT = "Input";
  static const char* LUA_PLAYER_RESOURCE = "PlayerResource";
  static const char* LUA_KEYCODE = "KEY";

  //global accessable table names
  static const char* LUA_ENTITY = "thisEntity";
  static const char* LUA_SCRIPT = "thisScript";
  static const char* LUA_ABILITY = "thisAbility";


  //names of metatable handlers
  static const char* LUA_HANDLER_ENTITY = "EntityH"; 
  static const char* LUA_HANDLER_LUA_SCRIPT = "LuaScriptH";
  static const char* LUA_HANDLER_SPRITE = "SpriteH";
  static const char* LUA_HANDLER_RIGIDBODY2D = "RigidBody2DH";
  static const char* LUA_HANDLER_PLAYER = "PlayerH";
  static const char* LUA_HANDLER_COLLISION_RECT = "CollisionRectH";
  static const char* LUA_HANDLER_COLLISION_CIRCLE = "CollisionCircleH";
  static const char* LUA_HANDLER_ANIMATOR = "AnimatorH";
  static const char* LUA_HANDLER_UNIT = "UnitH";
  static const char* LUA_HANDLER_ABILITY = "AbilityH";

  //onload function for main.lua
  static const char* LUA_ON_LOAD = "onLoad";

  //events for lua script
  static const char* LUA_ON_TICK = "onTick";
  static const char* LUA_ON_CREATE = "onCreate";
  static const char* LUA_ON_DESTROY = "onDestroy";

}

#endif