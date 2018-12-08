#include "ui_canvas.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>

#include "ui_image.h"
#include "ui_label.h"
#include <map>
#include <ui/ui_def.h>

#include <debug.h>

using namespace oak::ui;
using namespace oak;

std::vector<UINode*> UICanvas::nodes;

void UICanvas::render()
{
  for (uint i = 0; i < nodes.size(); i++)
  {
    if (nodes[i]->nodeType == UI_NODE_IMAGE)
    {
      UIImage* image = static_cast<UIImage*>(nodes[i]);
      UIImage::renderImage(image);
    }
    else if (nodes[i]->nodeType == UI_NODE_LABEL)
    {
      UILabel* label = static_cast<UILabel*>(nodes[i]);
      UILabel::renderLabel(label);
    }
  }
}

void UICanvas::onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
{
  //resize all the image nodes
  for (uint i = 0; i < nodes.size(); i++)
  {
    if (nodes[i]->nodeType == UI_NODE_IMAGE)
    {
      UIImage::setImageBuffer(
        static_cast<UIImage*>(nodes[i]), 
        windowToVPRatioX,
        windowToVPRatioY
      );
    }
  }
}

