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

Point& UINode::getParentPos()
{
  if (isRootNode)
  {
    return component->pos;
  }
  else
  {
    return parent->pos;
  }
}

ushort UINode::getTotalH()
{
  return (ushort)(margin.y * 2) + h;
}

void UINode::renderEnd(Point& nodeCursor)
{
  Point childCursor = { nodeCursor.x, nodeCursor.y };

  //calculate total height if automatic height
  if (isAutoH)
  {
    //margin and padding
    //h += (ushort)(margin.y + padding.y) * 2;

    for (auto node : children)
    {
      node->render(childCursor);
      if (node->positionType == UI_POSITION_RELATIVE)
      {
        ushort childNodeH = node->getTotalH();
        childCursor.y -= childNodeH;
        h += childNodeH; //height of each child node
      }
    }
    //h = totalH;
  }
  else
  {
    for (auto node : children)
    {
      node->render(childCursor);
      if (node->positionType == UI_POSITION_RELATIVE)
      {
        childCursor.y -= node->getTotalH();
      }
    }
  }

  nodeCursor.x -= offset.x + padding.x + margin.x;
  nodeCursor.y -= offset.y - padding.y - margin.y;
}

void UINode::renderBegin(Point& nodeCursor)
{
  Point parentPos = getParentPos();
  pos.x = parentPos.x + offset.x;
  pos.y = parentPos.y + offset.y;

  nodeCursor.x += offset.x + padding.x + margin.x;
  nodeCursor.y += offset.y - padding.y - margin.y;
}
