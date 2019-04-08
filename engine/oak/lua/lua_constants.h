#ifndef LUA_CONSTANTS_H
#define LUA_CONSTANTS_H

namespace oak
{
  static const char* LUA_ENTITY = "Entity"; //entity static functions
  static const char* LUA_ENTITY_HANDLE = "EntityH"; //entity handle instance
  static const char* LUA_SPRITE = "Sprite";
  static const char* LUA_VECTOR = "Vector";
  static const char* LUA_INPUT = "Input";

  //events for lua script
  static const char* LUA_ON_TICK = "onTick";
  static const char* LUA_ON_CREATE = "onCreate";
  static const char* LUA_ON_DESTROY = "onDestroy";
}

#endif