#ifndef UI_NODE_H
#define UI_NODE_H

#include "../core/types.h"
#include "ui_def.h"
#include <core/point.h>

namespace oak
{
  namespace ui
  {
    ///a ui node which
    struct UINode
    {
      UINode(const uchar nodeType)
      {
        this->nodeType = nodeType;
      }
      uchar nodeType;
      Point offset = { 0,0 };
      ushort w;
      ushort h;
      UINode* parent;
    };
  }
}

#endif