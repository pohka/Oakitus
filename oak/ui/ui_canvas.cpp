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

std::map<ushort, UIComponent*> UICanvas::components;
oak::Point UICanvas::projection = { 0,0 };
std::map<uint, std::string> strings;

void UICanvas::render()
{
  //get projection from font size to viewport to window coords
  glm::vec2 windowToVPRatio = Window::getWindowToVPRatio();
  float worldToVP = Window::worldToViewportCoords(1.0f);
  projection.x = windowToVPRatio.x * worldToVP;
  projection.y = windowToVPRatio.y * worldToVP;

  Point compPos;

  UIComponent* comp;
  for (std::map<ushort, UIComponent*>::iterator it = components.begin(); it != components.end(); ++it)
  {
    comp = it->second;
    compPos.x = (comp->offset.x * projection.x) + comp->align.x;
    compPos.y = (comp->offset.y * projection.y) + comp->align.y;

    for (UINode* node : comp->nodes)
    {
      if (node->nodeType == UI_NODE_IMAGE)
      {
        UIImage* image = static_cast<UIImage*>(node);
        UIImage::renderImage(image, compPos.x, compPos.y);
      }
      else if (node->nodeType == UI_NODE_LABEL)
      {
        UILabel* label = static_cast<UILabel*>(node);
        UILabel::renderLabel(label, compPos.x, compPos.y);
      }
    }
  }
}

void UICanvas::addComponent(ushort id, UIComponent* component)
{
  components.insert(std::pair<ushort, UIComponent*>(id, component));
}

UIComponent* UICanvas::getComponent(ushort id)
{
  return components[id];
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

const oak::Point& UICanvas::getProjection()
{
  return projection;
}
