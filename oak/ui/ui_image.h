#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#include <string>
#include "ui_node.h"
#include "ui_def.h"

namespace oak
{
  namespace ui
  {
    ///an image UI node
    struct UIImage : public UINode
    {
      UIImage()
      {
        nodeType = UI_NODE_IMAGE;
      }
      std::string src;
      uint VAO, VBO;
      uint textureID;

      ///creates and returns a new UIImage node
      static UIImage* createImage(std::string src, ushort w, ushort h);
      static void setImageBuffer(
        UIImage* img,
        float windowToVPRatioX,
        float windowToVPRatioY
      );
      ///renders a UI image
      static void renderImage(UIImage* img, float parentX, float parentY);
      ///deletes a ui image buffers
      static void removeImage(UIImage* img);
    };
  }
}

#endif