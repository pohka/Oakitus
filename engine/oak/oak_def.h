#ifndef OAK_DEF_H
#define OAK_DEF_H

#include "core/types.h"


//direction of an animation
cnum ANIM_DIRECTION_RIGHT = 0;
cnum ANIM_DIRECTION_LEFT = 1;

//all type of collision shapes
cnum COLLISION_SHAPE_RECT = 0;
cnum COLLISION_SHAPE_CIRCLE = 1;

cnum TICK_GROUP_DEFAULT = 0;
cnum TICK_GROUP_DURING_PHYSICS = 1;
cnum TICK_GROUP_AFTER_PHYSICS = 2;
cnum TICK_GROUP_LAST = 3;
cnum TICK_GROUP_MAX = 4;

cnum TICK_TYPE_NOT_TICKABLE = 0;
cnum TICK_TYPE_TICKABLE = 1;
cnum TICK_TYPE_INTERVAL_TICK = 2;
cnum TICK_TYPE_LAST = 3;



const char ENGINE_RESOURCES_ROOT_PATH [] = "../resources/";

#endif