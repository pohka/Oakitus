#include "ui_node.h"
#include "ui_component.h"
#include "ui_canvas.h"

using namespace oak::ui;
using namespace oak;



UINode::UINode(const uchar nodeType)
{
  this->nodeType = nodeType;
}
UINode::~UINode()
{
  for (uint i = 0; i < children.size(); i++)
  {
    delete children[i];
  }
  children.clear();
}

void UINode::setComponent(UIComponent* component)
{
  this->component = component;
}

void UINode::addChild(UINode* node)
{
  node->parent = this;
  node->isRootNode = false;
  node->component = component;
  children.push_back(node);
}

UINode* UINode::getParent()
{
  return parent;
}

uchar UINode::getType()
{
  return nodeType;
}

bool UINode::getIsRootNode()
{
  return isRootNode;
}

Point& UINode::getParentAbsolutePos()
{
  if (isRootNode)
  {
    return component->absolutePos;
  }
  else
  {
    return parent->absolutePos;
  }
}

void UINode::render()
{
  for (auto node : children)
  {
    node->render();
  }
}

void UINode::updateAbsolutePos()
{
  Point parentPos = getParentAbsolutePos();
  absolutePos.x = parentPos.x + offset.x;
  absolutePos.y = parentPos.y + offset.y;
}