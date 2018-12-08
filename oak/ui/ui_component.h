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
      uchar alignment;
      std::vector<UINode*> nodes;
    };
  }
}

#endif