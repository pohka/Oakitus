#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "ui_def.h"
#include <vector>
#include "ui_node.h"
#include <core/point.h>
#include "localization.h"

namespace oak
{
  namespace ui
  {
    ///a container for UI nodes
    struct UIComponent
    {
      std::vector<UINode*> nodes;
      Point align = { 
        UI_ALIGN_HORZ_LEFT, 
        UI_ALIGN_VERT_TOP 
      };
      Point offset = { 0,0 };
    };
  }
}

#endif