#ifndef UI_CANVAS_H
#define UI_CANVAS_H

#include "ui_element.h"
#include <vector>

namespace oak
{
  namespace ui
  {
    class UICanvas
    {
      static std::vector<UIElement*> elements;

      public:
        static void render();
        static void addElement(UIElement* element);
    };
  }
}

#endif