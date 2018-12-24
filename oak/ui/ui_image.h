#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#include <string>
#include "ui_node.h"
#include "ui_def.h"

namespace ion
{
  ///an image UI node
  struct UIImage : public UINode
  {
    UIImage(std::string src, ushort w, ushort h);
    ~UIImage();
    std::string src;
    uint VAO, VBO;
    uint textureID;

    void setTexture(std::string src);

    void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);
    ///renders a UI image
    void render(UIPoint& nodeCursor);
  };
}

#endif