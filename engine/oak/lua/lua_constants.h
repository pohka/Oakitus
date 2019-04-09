#ifndef LUA_CONSTANTS_H
#define LUA_CONSTANTS_H

namespace oak
{
  static const char* LUA_ENTITY = "Entity"; //entity static functions
  static const char* LUA_VECTOR = "Vector";
  static const char* LUA_INPUT = "Input";
  static const char* LUA_PLAYER_RESOURCE = "PlayerResource";
  static const char* LUA_KEYCODE = "KEY";

  static const char* LUA_HANDLE_ENTITY = "EntityH"; //entity handle instance
  static const char* LUA_HANDLE_SPRITE = "SpriteH";
  static const char* LUA_HANDLE_RIGIDBODY2D = "RigidBody2DH";
  static const char* LUA_HANDLE_PLAYER = "PlayerH";


  //events for lua script
  static const char* LUA_ON_TICK = "onTick";
  static const char* LUA_ON_CREATE = "onCreate";
  static const char* LUA_ON_DESTROY = "onDestroy";
}

#endif