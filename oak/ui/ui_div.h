#ifndef UI_DIV_H
#define UI_DIV_H

#include "ui_node.h"

namespace oak
{
  namespace ui
  {
    struct UIDiv : public UINode
    {
      UIDiv();
      ~UIDiv();

      void render(Point& nodeCursor);
      void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);
    };
  }
}

#endif