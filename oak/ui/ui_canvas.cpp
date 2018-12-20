#include "ui_canvas.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>

#include "ui_image.h"
#include "ui_label.h"
#include <map>
#include <ui/ui_def.h>
#include <core/input.h>

#include <debug.h>

using namespace oak::ui;
using namespace oak;

std::map<ushort, UIComponent*> UICanvas::components;
oak::Point UICanvas::projection = { 0,0 };
std::map<uint, std::string> strings;
std::vector<Style*> UICanvas::styles;

void UICanvas::render()
{
  ushort ptX = (ushort)Input::mousePos.x;
  ushort ptY = (ushort)Input::mousePos.y;
  for (std::map<ushort, UIComponent*>::iterator it = components.begin(); it != components.end(); ++it)
  {
   // it->second->events();
    it->second->onBeforeRender();
  }

  //get projection from font size to viewport to window coords
  glm::vec2 windowToVPRatio = Window::getWindowToVPRatio();
  float worldToVP = Window::worldToViewportCoords(1.0f);
  projection.x = windowToVPRatio.x * worldToVP;
  projection.y = windowToVPRatio.y * worldToVP;

  for (std::map<ushort, UIComponent*>::iterator it = components.begin(); it != components.end(); ++it)
  {
    it->second->render(projection);
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
  for (auto comp : components)
  {
    comp.second->onWindowResize(windowToVPRatioX, windowToVPRatioY);
  }
}

const oak::Point& UICanvas::getProjection()
{
  return projection;
}


Style* UICanvas::findStyle(std::string cls)
{
  for (Style* style : styles)
  {
    for (uint i = 0; i < style->classList.size(); i++)
    {
      if (style->classList[i] == cls)
      {
        return style;
      }
    }
  }
  return nullptr;
}