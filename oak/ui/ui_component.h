#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "ui_def.h"
#include <vector>
#include "ui_node.h"

namespace oak
{
  namespace ui
  {
    struct UIComponent
    {
      std::vector<UINode*> nodes;
      float alignX = UI_ALIGN_HORZ_LEFT;
      float alignY = UI_ALIGN_VERT_TOP;
    };
  }
}

#endif