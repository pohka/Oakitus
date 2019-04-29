#pragma once
#ifndef OAK_DEF_H
#define OAK_DEF_H

#include "core/types.h"

namespace oak
{
  //direction of an animation
  enum class AnimDirection : uchar
  {
    RIGHT = 0,
    LEFT = 1
  };

  enum class TickGroup : uchar
  {
    DEFAULT = 0,
    DURING_PHYSICS = 1,
    AFTER_PHYSICS = 2,
    LAST = 3,
    COUNT = 4
  };

  enum class TickType : uchar
  {
    NOT_TICKABLE = 0,
    TICKABLE = 1,
    INTERVAL_TICK = 2,
    COUNT = 3
  };

  enum class ReflectID : ushort
  {
    NONE = 0,
    TRANSFORM = 1,
    ANIMATOR = 2,
    RIGID_BODY_2D = 3,
    SPRITE = 4,
    CHUNK = 5,
    LUA_SCRIPT = 6,
    UNIT = 7,
    COUNT = 8
  };

  enum class AnimID : uchar
  {
    NONE = 0,
    IDLE,
    RUN,
    DEATH,
    ABILITY_1,
    ABILITY_2,
    ABILITY_3,
    ABILITY_4
  };
}

//direction of an animation
//cnum ANIM_DIRECTION_RIGHT = 0;
//cnum ANIM_DIRECTION_LEFT = 1;

//all type of collision shapes
//cnum COLLISION_SHAPE_RECT = 0;
//cnum COLLISION_SHAPE_CIRCLE = 1;

//ticking groups for components
cnum TICK_GROUP_DEFAULT = 0;
cnum TICK_GROUP_DURING_PHYSICS = 1;
cnum TICK_GROUP_AFTER_PHYSICS = 2;
cnum TICK_GROUP_LAST = 3;
cnum TICK_GROUP_MAX = 4;

//ticking types for components
cnum TICK_TYPE_NOT_TICKABLE = 0;
cnum TICK_TYPE_TICKABLE = 1;
cnum TICK_TYPE_INTERVAL_TICK = 2;
cnum TICK_TYPE_LAST = 3;

//state of an entity in creation
//cnum CREATION_STATE_NULL = 0; //not queued or created
//cnum CREATION_STATE_QUEUED = 1; //in queue to be created at the end of the frame
//cnum CREATION_STATE_CREATED = 2; //created
//cnum CREATION_STATE_DESTROYED = 3; //queued for destruction

//reflections
static const uint REFLECT_NULL = 0;
static const uint REFLECT_TRANSFORM = 1;
static const uint REFLECT_ANIMATOR = 2;
static const uint REFLECT_RIGID_BODY_2D = 3;
static const uint REFLECT_SPRITE = 4;
static const uint REFLECT_CHUNK = 5;
static const uint REFLECT_LUA_SCRIPT = 6;
static const uint REFLECT_UNIT = 7;
static const uint REFLECT_LAST = 7;

//entity groups
cnum ENTITY_GROUP_NONE = 0;
cnum ENTITY_GROUP_ACTOR = 1;
cnum ENTITY_GROUP_WORLD = 2;

cnum ANIM_NULL = 0;
cnum ANIM_IDLE = 1;
cnum ANIM_RUN = 2;
cnum ANIM_DEATH = 3;


const char ENGINE_RESOURCES_ROOT_PATH [] = "../../resources/";


#endif