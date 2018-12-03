#ifndef GAME_DEF_H
#define GAME_DEF_H

#include <core/types.h>

//ability casting states
cnum CAST_STATE_NONE = 0;
cnum CAST_STATE_PRECAST = 1;
cnum CAST_STATE_CASTING = 2;

//ability target type
cnum TARGET_TYPE_NONE = 0;
cnum TARGET_TYPE_NO_TARGET = 1;
cnum TARGET_TYPE_POINT = 2;
cnum TARGET_TYPE_UNIT_TARGET = 3;

//target team
cnum TARGET_TEAM_NONE = 0;
cnum TARGET_TEAM_FRIENDLY = 1;
cnum TARGET_TEAM_ENEMY = 2;
cnum TARGET_TEAM_BOTH = 3;

//animation types
cnum ANIM_TYPE_NONE = 0;
cnum ANIM_TYPE_IDLE = 1;
cnum ANIM_TYPE_RUN = 2;
cnum ANIM_TYPE_ATTACK = 3;
cnum ANIM_TYPE_ABILITY_1 = 4;
cnum ANIM_TYPE_ABILITY_2 = 5;
cnum ANIM_TYPE_ABILITY_3 = 6;
cnum ANIM_TYPE_ABILITY_4 = 7;

//animation priority
cnum ANIM_PRIORITY_LOWEST = 0;
cnum ANIM_PRIORITY_BASE = 1;
cnum ANIM_PRIORITY_ABILITY = 2;
cnum ANIM_PRIORITY_DISABLE = 3;

//factions
cnum FACTION_NONE = 0;
cnum FACTION_PLAYER = 1;
cnum FACTION_ENEMY = 2;

#endif