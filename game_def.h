#ifndef GAME_DEF_H
#define GAME_DEF_H

#include <core/types.h>

//ability casting states
cnum CAST_STATE_NONE =    0;
cnum CAST_STATE_PRECAST = 1;
cnum CAST_STATE_CASTING = 2;

//ability target type
cnum TARGET_TYPE_NONE =         0;
cnum TARGET_TYPE_NO_TARGET =    1;
cnum TARGET_TYPE_POINT =        2;
cnum TARGET_TYPE_UNIT_TARGET =  3;

//target team
cnum TARGET_TEAM_NONE =     0;
cnum TARGET_TEAM_FRIENDLY = 1;
cnum TARGET_TEAM_ENEMY =    2;
cnum TARGET_TEAM_BOTH =     3;

//animation types
cnum ANIM_TYPE_NONE =       0;
cnum ANIM_TYPE_IDLE =       1;
cnum ANIM_TYPE_RUN =        2;
cnum ANIM_TYPE_ATTACK =     3;
cnum ANIM_TYPE_ABILITY_1 =  4;
cnum ANIM_TYPE_ABILITY_2 =  5;
cnum ANIM_TYPE_ABILITY_3 =  6;
cnum ANIM_TYPE_ABILITY_4 =  7;

//animation priority
cnum ANIM_PRIORITY_LOWEST =   0;
cnum ANIM_PRIORITY_BASE =     1;
cnum ANIM_PRIORITY_ABILITY =  2;
cnum ANIM_PRIORITY_DISABLE =  3;

//factions
cnum FACTION_NONE = 0;
cnum FACTION_PLAYER = 1;
cnum FACTION_ENEMY = 2;

//event types
cnum EVENT_ON_NONE =          0;
cnum EVENT_ON_DAMAGE_TAKEN =  1;
cnum EVENT_ON_DEATH =         2;

//element types
cnum ELEMENT_NORMAL =   0;
cnum ELEMENT_FIRE =     1;
cnum ELEMENT_GRASS =    2;
cnum ELEMENT_WATER =    3;
cnum ELEMENT_ICE =      4;
cnum ELEMENT_ELECTRIC = 5;
cnum ELEMENT_WIND =     6;
cnum ELEMENT_COUNT = 7;

//modifier properties
cnum MODIFIER_PROP_HEALTH = 0;

cnum MODIFIER_PROP_MANA = 2;
cnum MODIFIER_PROP_MOVESPEED = 4;
//element resists
//note: must be in same order element types
cnum MODIFIER_PROP_RESIST_NORMAL = 5;
cnum MODIFIER_PROP_RESIST_FIRE = 6;
cnum MODIFIER_PROP_RESIST_GRASS = 7;
cnum MODIFIER_PROP_RESIST_WATER = 8;
cnum MODIFIER_PROP_RESIST_ICE = 9;
cnum MODIFIER_PROP_RESIST_ELECTRIC = 10;
cnum MODIFIER_PROP_RESIST_WIND = 11;
//element amplify
//note: must be in same order element types
cnum MODIFIER_PROP_AMP_NORMAL = 12;
cnum MODIFIER_PROP_AMP_FIRE = 13;
cnum MODIFIER_PROP_AMP_GRASS = 14;
cnum MODIFIER_PROP_AMP_WATER = 15;
cnum MODIFIER_PROP_AMP_ICE = 16;
cnum MODIFIER_PROP_AMP_ELECTRIC = 17;
cnum MODIFIER_PROP_AMP_WIND = 18;

cnum MODIFIER_PROP_NORMAL_DAMAGE = 19;
cnum MODIFIER_PROP_FIRE_DAMAGE = 20;
cnum MODIFIER_PROP_GRASS_DAMAGE = 21;
cnum MODIFIER_PROP_WATER_DAMAGE = 22;
cnum MODIFIER_PROP_ICE_DAMAGE = 23;
cnum MODIFIER_PROP_ELECTRIC_DAMAGE = 24;
cnum MODIFIER_PROP_WIND_DAMAGE = 25;

//item quality
cnum ITEM_QUALITY_COMMON = 0;
cnum ITEM_QUALITY_UNCOMMON = 1;
cnum ITEM_QUALITY_RARE = 2;
cnum ITEM_QUALITY_EPIC = 3;
cnum ITEM_QUALITY_LEGENDARY = 4;
cnum ITEM_QUALITY_MYTHICAL = 5;

//item slots
cnum ITEM_SLOT_NONE = 0;
cnum ITEM_SLOT_ARMOR = 1;
cnum ITEM_SLOT_WEAPON = 2;
cnum ITEM_SLOT_BOOTS = 3;


#endif