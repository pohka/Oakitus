#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <vector>
#include <string>
#include "ui_def.h"

namespace oak
{
  namespace ui
  {
    struct UIElement
    {
        std::vector<UIElement*> children;
        std::string textContent = "";
        uchar alignment = UI_ALIGN_MIDDLE_CENTER;
        short x = 0;
        short y = 0;
        ushort w = 1;
        ushort h = 1;
    };
  }
}

#endif