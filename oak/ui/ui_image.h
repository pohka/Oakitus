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
      UIImage(std::string src, ushort w, ushort h);
      std::string src;
      uint VAO, VBO;
      uint textureID;
      
      void setImageBuffer(
        float windowToVPRatioX,
        float windowToVPRatioY
      );
      ///renders a UI image
      void render(float parentX, float parentY);
      ///deletes a ui image buffers
      void remove();
    };
  }
}

#endif