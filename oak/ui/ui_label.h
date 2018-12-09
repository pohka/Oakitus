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
    ///a label has data that will display text
    struct UILabel : public UINode
    {
      UILabel()
      {
        nodeType = UI_NODE_LABEL;
      }

      std::string text;
      float scale = 1.0f; //font scale
      uint VAO, VBO;
      Color color;
      uchar fontID;

      ///creates and returns a new label
      static UILabel* createLabel(std::string src, ushort fontSize, ushort w, ushort h);
      ///renders a label
      static void renderLabel(UILabel* label, float parentX, float parentY);
    };
  }
}

#endif