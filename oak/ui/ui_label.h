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
      UILabel(std::string src, ushort fontSize, ushort w, ushort h);

      std::string text;
      float scale = 1.0f; //font scale
      uint VAO, VBO;
      Color color;
      uchar fontID;
      ///renders a label
      void render(float parentX, float parentY);
    };
  }
}

#endif