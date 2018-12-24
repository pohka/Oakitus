#include "ui_canvas.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>

#include "ui_image.h"
#include "ui_label.h"
#include <map>
#include <ui/ui_def.h>
#include <core/input.h>
#include <ui/style_parser.h>

#include <debug.h>

using namespace ion;

std::map<ushort, UIComponent*> UICanvas::components;
UIPoint UICanvas::projection = { 0,0 };
std::map<uint, std::string> strings;
std::vector<Style*> UICanvas::styles;

void UICanvas::render()
{
  ushort ptX = (ushort)oak::Input::mousePos.x;
  ushort ptY = (ushort)oak::Input::mousePos.y;
  for (std::map<ushort, UIComponent*>::iterator it = components.begin(); it != components.end(); ++it)
  {
   // it->second->events();
    it->second->onBeforeRender();
  }

  

  //get projection from font size to viewport to window coords
  glm::vec2 windowToVPRatio = oak::Window::getWindowToVPRatio();
  float worldToVP = oak::Window::worldToViewportCoords(1.0f);
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

const UIPoint& UICanvas::getProjection()
{
  return projection;
}


Style* UICanvas::findStyle(std::string selector)
{
  for (Style* style : styles)
  {
    if (style->selector == selector)
    {
      return style;
    }
  }
  return nullptr;
}

//note: state styles will be deleted if the selector is not parsed correctly
void UICanvas::addStyle(Style* style)
{
  //check if state style (pseudo style), example: myclass:hover
  bool isStateStyle = false;
  for (uint i = 0; i < style->selector.size() && !isStateStyle; i++)
  {
    if (style->selector[i] == ':' && style->selector.size() >= i+1)
    {
      isStateStyle = true;
      std::string stateName = style->selector.substr(i + 1);
      uchar stateID = StyleParser::parseStateID(stateName);
      if (stateID != STYLE_STATE_NONE)
      {
        std::string selectorName = style->selector.substr(0, i);
        Style* s = findStyle(selectorName);
        if (s != nullptr)
        {
          bool success = s->addStateStyle(stateID, style);
          if (!success)
          {
            delete style;
            LOG << "---STYLE ERROR---| '" << style->selector << "' state style not set as parent was not found";
          }
        }
      }
      else
      {
        delete style;
        LOG << "---STYLE ERROR---| state id not found for '"<< stateName <<"'";
      }
    }
  }
  if (!isStateStyle)
  {
    styles.push_back(style);
  }
}

void UICanvas::deleteAllStyles()
{
  for (auto it = styles.begin(); it != styles.end(); ++it)
  {
    delete (*it);
  }
  styles.clear();
}