#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#include <string>
#include "ui_node.h"
#include "ui_def.h"

namespace oak
{
  namespace ui
  {
    struct UIImage : public UINode
    {
      UIImage()
      {
        nodeType = UI_NODE_IMAGE;
      }
      std::string src;
      uint VAO, VBO;
      uint textureID;

      static UIImage* createImage(std::string src, ushort w, ushort h);
      static void setImageBuffer(
        UIImage* img,
        float windowToVPRatioX,
        float windowToVPRatioY
      );
      static void renderImage(UIImage* img);
      static void removeImage(UIImage* img);
    };
  }
}

#endif