#include "ui_component.h"
#include <core/input.h>

using namespace ion;
using namespace oak;


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
  node->calcStyle();
  node->setComponent(this);
  nodes.push_back(node);
}

void UIComponent::recalcStyle()
{
  for (uint i = 0; i < nodes.size(); i++)
  {
    nodes[i]->calcStyle();
  }
}