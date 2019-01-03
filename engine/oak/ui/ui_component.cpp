#include "ui_component.h"
#include <oak/input/input.h>
#include <oak/debug.h>

using namespace ion;
using namespace oak;


UIComponent::~UIComponent()
{
  for (uint i = 0; i < nodes.size(); i++)
  {
    delete nodes[i];
  }
  nodes.clear();
}

void UIComponent::render(UIPoint& projection)
{
  glm::vec2 windowUnit = Window::getWindowUnitToPixel();

  pos.x = offset.x + (align.x * windowUnit.x);
  pos.y = offset.y + (align.y * windowUnit.y);

  UIPoint nodeCursor = {
    pos.x + margin.x + padding.x,
    pos.y + margin.y + padding.y
  };

  for (UINode* node : nodes)
  {
    node->render(nodeCursor);
  }
}

void UIComponent::onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
{
  for (UINode* node : nodes)
  {
    node->onWindowResize(windowToVPRatioX, windowToVPRatioY);
  }
}

void UIComponent::addNode(UINode* node)
{
  node->computeStyle();
  node->setComponent(this);
  nodes.push_back(node);
}

void UIComponent::recomputeStyle()
{
  for (uint i = 0; i < nodes.size(); i++)
  {
    nodes[i]->computeStyle();
  }
}

UINode* UIComponent::findNodeByID(std::string id)
{
  for (uint i = 0; i < nodes.size(); i++)
  {
    if (nodes[i]->id == id)
    {
      return nodes[i];
    }
    else
    {
      UINode* node = nodes[i]->findNodeByID(id);
      if (node != nullptr)
      {
        return node;
      }
    }
  }
  return nullptr;
}