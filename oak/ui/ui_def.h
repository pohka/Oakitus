#ifndef UI_DEF_H
#define UI_DEF_H

#include "../core/types.h"

namespace oak
{
  namespace ui
  {
    //alignment types
    //cnum UI_ALIGN_TOP_LEFT =       0;
    //cnum UI_ALIGN_TOP_CENTER =     1;
    //cnum UI_ALIGN_TOP_RIGHT =      2;
    //cnum UI_ALIGN_BOTTOM_LEFT =    3;
    //cnum UI_ALIGN_BOTTOM_CENTER =  4;
    //cnum UI_ALIGN_BOTTOM_RIGHT =   5;
    //cnum UI_ALIGN_MIDDLE_LEFT =    6;
    //cnum UI_ALIGN_MIDDLE_CENTER =  7;
    //cnum UI_ALIGN_MIDDLE_RIGHT =   8;

    cnum UI_NODE_LABEL = 0;
    cnum UI_NODE_IMAGE = 1;

    //alignment values
    const float UI_ALIGN_HORZ_LEFT = -1.0f;
    const float UI_ALIGN_HORZ_CENTER = 0.0f;
    const float UI_ALIGN_HORZ_RIGHT = 1.0f;

    const float UI_ALIGN_VERT_TOP = 1.0f;
    const float UI_ALIGN_VERT_MIDDLE = 0.0f;
    const float UI_ALIGN_VERT_BOTTOM = -1.0f;
  }
}

#endif