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

std::vector<UIComponent*> UICanvas::components;

void UICanvas::render()
{
  for (UIComponent* comp : components)
  {
    for (UINode* node : comp->nodes)
    {
      if (node->nodeType == UI_NODE_IMAGE)
      {
        UIImage* image = static_cast<UIImage*>(node);
        UIImage::renderImage(image, comp->alignX, comp->alignY);
      }
      else if (node->nodeType == UI_NODE_LABEL)
      {
        UILabel* label = static_cast<UILabel*>(node);
        UILabel::renderLabel(label);
      }
    }
  }
}

void UICanvas::onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
{
  //resize all the image nodes
  for (uint i = 0; i < components.size(); i++)
  {
    for (UINode* node : components[i]->nodes)
    {
      if (node->nodeType == UI_NODE_IMAGE)
      {
        UIImage::setImageBuffer(
          static_cast<UIImage*>(node),
          windowToVPRatioX,
          windowToVPRatioY
        );
      }
    }
  }
}
