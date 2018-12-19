#ifndef UI_DEF_H
#define UI_DEF_H

#include "../core/types.h"


cnum UI_NODE_LABEL = 0;
cnum UI_NODE_IMAGE = 1;
cnum UI_NODE_DIV = 2;
cnum UI_NODE_TEMPLATE = 3;


//alignment values
const float UI_ALIGN_HORZ_LEFT = -1.0f;
const float UI_ALIGN_HORZ_CENTER = 0.0f;
const float UI_ALIGN_HORZ_RIGHT = 1.0f;

const float UI_ALIGN_VERT_TOP = 1.0f;
const float UI_ALIGN_VERT_MIDDLE = 0.0f;
const float UI_ALIGN_VERT_BOTTOM = -1.0f;

const uint FONT_LOADED_SIZE = 64;

cnum UI_POSITION_RELATIVE = 0;
cnum UI_POSITION_ABSOLUTE = 1;

#endif