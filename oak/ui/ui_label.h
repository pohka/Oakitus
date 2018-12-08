#ifndef UI_LABEL_H
#define UI_LABEL_H

#include "ui_node.h"
#include <string>
#include "ui_def.h"
#include "color.h"
#include "font.h"

namespace oak
{
  namespace ui
  {
    struct UILabel : public UINode
    {
      UILabel()
      {
        nodeType = UI_NODE_LABEL;
      }

      std::string text;
      float scale = 1.0f;
      uint VAO, VBO;
      Color color;
      uchar fontID;

      static UILabel* createLabel(std::string src, ushort w, ushort h);
      static void renderLabel(UILabel* label);
    };
  }
}

#endif